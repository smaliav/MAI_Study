#include <stdio.h>
#include <math.h>
#include <string.h>

#define CSC(call) \
do { \
	cudaError_t res = call; \
	if (res != cudaSuccess) { \
		fprintf(stderr, "ERROR: file:%s line:%d message:%s\n", \
				__FILE__, __LINE__, cudaGetErrorString(res)); \
		exit(0); \
	} \
} while (0)

#define DIM3 3
#define R 0
#define G 1
#define B 2
#define MAX_NC 32
#define N_INF_FLOAT __int_as_float(0xff800000)

typedef struct _arr3 {
    double data[DIM3];
} arr3;

typedef struct _pxlClass {
    int size;
    int* x;
    int* y;
    arr3 avg;
} pxlClass;

typedef struct _image {
    int width;
    int height;
    uchar4* pixels;
} image;

void writeImage(const char* filename, const image* img) {
    FILE* output = fopen(filename, "wb");

    fwrite(&img->width, sizeof(img->width), 1, output);
    fwrite(&img->height, sizeof(img->height), 1, output);
    fwrite(img->pixels, sizeof(img->pixels), img->height * img->width, output);

    fclose(output);
}

void deleteImage(image* img) {
    free(img->pixels);
    free(img);
    img = NULL;
}

image* readImage(const char* filename) {
    image* img = (image *)malloc(sizeof(image));
    
    FILE* input = fopen(filename, "rb");

    fread(&img->width, sizeof(img->width), 1, input);
    fread(&img->height, sizeof(img->height), 1, input);

    img->pixels = (uchar4 *)malloc(sizeof(uchar4) * img->height * img->width);
    fread(img->pixels, sizeof(img->pixels), img->height * img->width, input);
    
    fclose(input);

    return img;
}

__device__ __host__ int pos2Dto1D(int x, int y, int width) {
    return x + y * width;
}

pxlClass* readClasses(const int nc, const image* img) {
    pxlClass* pxlC = (pxlClass *)malloc(sizeof(pxlClass) * nc);
    
    for (int i = 0; i < nc; ++i) {
        int np;

        scanf("%d", &np);

        pxlC[i].x = (int *)malloc(sizeof(int) * np);
        pxlC[i].y = (int *)malloc(sizeof(int) * np);

        memset(pxlC[i].avg.data, 0.0, sizeof(pxlC[i].avg.data));
        
        for (int j = 0; j < np; ++j) {
            scanf("%d %d", &(pxlC[i].x[j]), &(pxlC[i].y[j]));

            uchar4 pixel = img->pixels[pos2Dto1D(pxlC[i].x[j], pxlC[i].y[j], img->width)];

            pxlC[i].avg.data[R] += pixel.x;
            pxlC[i].avg.data[G] += pixel.y;
            pxlC[i].avg.data[B] += pixel.z;
        }

        pxlC[i].avg.data[R] /= (double)np;
        pxlC[i].avg.data[G] /= (double)np;
        pxlC[i].avg.data[B] /= (double)np;
    }

    return pxlC;
}

__constant__ arr3 avgC[MAX_NC];

void deleteClasses(pxlClass* pxlC) {
    free(pxlC->x);
    free(pxlC->y);
    free(pxlC);

    pxlC = NULL;
}

__device__ double calcMinDist(const uchar4* pixel, int idx) {
    double dist = 0.0;
    arr3 value;

    value.data[R] = pixel->x - avgC[idx].data[R];
    value.data[G] = pixel->y - avgC[idx].data[G];
    value.data[B] = pixel->z - avgC[idx].data[B];

    for (int i = 0; i < DIM3; ++i) {
        dist += value.data[i] * value.data[i];
    }

    return -dist;
}

__global__ void minDist(uchar4* res, int width, int height, int nc) {
    int idX = blockIdx.x * blockDim.x + threadIdx.x;
    int idY = blockIdx.y * blockDim.y + threadIdx.y;
    int offsetX = gridDim.x * blockDim.x;
    int offsetY = gridDim.y * blockDim.y;

    for (int i = idX; i < width; i += offsetX) {
        for (int j = idY; j < height; j += offsetY) {
            int pos = pos2Dto1D(i, j, width);
            double maxDist = N_INF_FLOAT;
            int maxIdx = 0;

            for (int k = 0; k < nc; ++k) {
                double dist = calcMinDist(&res[pos], k);

                if (dist > maxDist) {
                    maxDist = dist;
                    maxIdx = k;
                }
            }

            res[pos].w = maxIdx;
        }
    }
}

void printHexPixels(const image *img) {
    for (int x = 0; x < img->width; x++) {
        for (int y = 0; y < img->height; ++y) {
            uchar4 p = img->pixels[x + y * img->width];

            printf("PXL %f %f %f %f\n", (float)p.x, (float)p.y, (float)p.z, (float)p.w);
        }
    }
}

void printArray(float *arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("DEBUG %f\n", arr[i]);
    }
}

int main(int argc, char const *argv[]) {
    char srcFilename[256];
    char resFilename[256];
    int nc;

    scanf("%s", srcFilename);
    scanf("%s", resFilename);

    image *img = readImage(srcFilename);

    scanf("%d", &nc);
    pxlClass* pxlC = readClasses(nc, img);
    uchar4 *resDist;
    CSC(cudaMalloc(&resDist, sizeof(uchar4) * img->width * img->height));
    CSC(cudaMemcpy(resDist, img->pixels, sizeof(uchar4) * img->width * img->height, cudaMemcpyHostToDevice));
    
    for (int i = 0; i < nc; ++i) {
        CSC(cudaMemcpyToSymbol(avgC, &(pxlC[i].avg), sizeof(arr3), i * sizeof(arr3)));
    }

    dim3 grid(16, 16);
    dim3 block(16, 16);

    minDist<<<grid, block>>>(resDist, img->width, img->height, nc);

    CSC(cudaGetLastError());

    CSC(cudaMemcpy(img->pixels, resDist, sizeof(uchar4) * img->height * img->width,
        cudaMemcpyDeviceToHost));
    writeImage(resFilename, img);

    deleteClasses(pxlC);
    deleteImage(img);

    return 0;
}
