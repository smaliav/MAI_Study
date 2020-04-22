#include <thrust/device_vector.h>
#include <thrust/extrema.h>

#include <cmath>
#include <time.h>
#include <iostream>

#define CSC(call) \
do { \
	cudaError_t res = call; \
	if (res != cudaSuccess) { \
		fprintf(stderr, "ERROR: file:%s line:%d message:%s\n", \
				__FILE__, __LINE__, cudaGetErrorString(res)); \
		exit(0); \
	} \
} while (0)

typedef struct _comparator {
    __device__ __host__ bool operator()(double a, double b) {
        return std::fabs(a) < std::fabs(b);
    }
} comparator;

__device__ __host__ int pos2Dto1D(int x, int y, int width) {
    return x + y * width;
}

__global__ void subtractProductKernel(double *mtx, int size, int i) {
    int idX = blockDim.x * blockIdx.x + threadIdx.x;
    int idY = blockDim.y * blockIdx.y + threadIdx.y;
    int offsetX = blockDim.x * gridDim.x;
    int offsetY = blockDim.y * gridDim.y;

    for (int j = idX + i + 1; j < size; j += offsetX) {
        for (int k = idY + i + 1; k < size; k += offsetY) {
            mtx[pos2Dto1D(j, k, size)] -= mtx[pos2Dto1D(j, i, size)] * mtx[pos2Dto1D(i, k, size)];
        }
    }
}

__global__ void divideKernel(double *mtx, int size, int columnIdx) {
    int idX = columnIdx + threadIdx.x + blockIdx.x * blockDim.x + 1;
    int offsetX = blockDim.x * gridDim.x;

    while (idX < size) {
        mtx[pos2Dto1D(idX, columnIdx, size)] /= mtx[pos2Dto1D(columnIdx, columnIdx, size)];
        idX += offsetX;
    }
}

__global__ void swapKernel(double *mtx, int size, int strIdx, int swapIdx) {
    int idX = blockDim.x * blockIdx.x + threadIdx.x;
    int offsetX = blockDim.x * gridDim.x;
    double swapTmp;

    for (int i = idX; i < size; i += offsetX) {
        swapTmp = mtx[pos2Dto1D(strIdx, i, size)];
        mtx[pos2Dto1D(strIdx, i, size)] = mtx[pos2Dto1D(swapIdx, i, size)];
        mtx[pos2Dto1D(swapIdx, i, size)] = swapTmp;
    }
}

void printSquareMatrix(const double *mtx, const int &size) {
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            printf("%lf ", mtx[pos2Dto1D(x, y, size)]);
        }

        printf("\n");
    }
}

void printVector(const int *vec, const int &size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", vec[i]);
    }

    printf("\n");
}

void initPermVec(int *p, const int &size) {
    for (int i = 0; i < size; ++i) {
        p[i] = i;
    }
}

void readSquareMatrix(double *mtx, const int &size) {
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            scanf("%lf", &mtx[pos2Dto1D(x, y, size)]);  // Check %lf -> %f
        }
    }
}

void printAnswer(const double *mtx, const int *p, const int &size) {
    std::cout.precision(11);

    // Print C matrix
    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            std::cout << std::fixed << mtx[pos2Dto1D(x, y, size)] << " ";
        }

        std::cout << std::endl;
    }
    
    // Print permutation vector
    for (int i = 0; i < size; ++i) {
        std::cout << p[i] << " ";
    }

    std::cout << std::endl;
}

int main(int argc, const char **argv) {
    // TODO Implement time calculation
    comparator compare;

    int size;           // Size of initial matrix
    scanf("%d", &size);

    // Read initial matrix
    double *mtx = (double *)malloc(sizeof(double) * size * size);
    readSquareMatrix(mtx, size);
    // printSquareMatrix(mtx, size);   // DEBUG

    // Initialize permutation vector
    int *p = (int *)malloc(sizeof(int) * size);
    initPermVec(p, size);
    // printVector(p, size);   // DEBUG

    // Initialize CUDA matrix
    double *cudaMtx;
    CSC(cudaMalloc(&cudaMtx, sizeof(double) * size * size));
    CSC(cudaMemcpy(cudaMtx, mtx, sizeof(double) * size * size, cudaMemcpyHostToDevice));

    // Main algorithm
    thrust::device_ptr<double> ptr = thrust::device_pointer_cast(cudaMtx);

    for (int i = 0; i < size - 1; ++i) {
        // Searching for max element
        thrust::device_ptr<double> maxElem = thrust::max_element(ptr + i + i * size,
            ptr + i * size + size, compare);
        
        int maxIdx = maxElem - ptr - i * size;
        p[i] = maxIdx;

        // Swap i string and string with max element
        if (maxIdx != i) {
            swapKernel<<<32, 256>>>(cudaMtx, size, i, maxIdx);
        }

        // Divide column by max element
        divideKernel<<<32, 256>>>(cudaMtx, size, i);

        // Subtract the product of Cji and Cik from Cjk
        subtractProductKernel<<<dim3(32, 32), dim3(32, 32)>>>(cudaMtx, size, i);
    }

    CSC(cudaMemcpy(mtx, cudaMtx, sizeof(double) * size * size, cudaMemcpyDeviceToHost));
    // printSquareMatrix(mtx, size);   // DEBUG

    printAnswer(mtx, p, size);

    CSC(cudaFree(cudaMtx));
    free(mtx);
    free(p);

    return 0;
}
