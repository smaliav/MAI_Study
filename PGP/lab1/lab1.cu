#include <stdio.h>
#include <stdlib.h>

#define CSC(call)												\
do {															\
	cudaError_t res = call;										\
	if (res != cudaSuccess) {									\
		fprintf(stderr, "ERROR: file:%s line:%d message:%s\n",	\
				__FILE__, __LINE__, cudaGetErrorString(res));	\
		exit(0);												\
	}															\
} while (0)

__global__ void kernel(double *devVec, double *revVec, int n) {
	int idx = threadIdx.x + blockIdx.x * blockDim.x;
	int offset = blockDim.x + gridDim.x;

	while (idx < n) {
		revVec[idx] = devVec[n - 1 - idx];

		idx += offset;
	}
}

void printVector(double *vec, int size) {
	for (int i = 0; i < size; ++i) {
		printf("%f ", vec[i]);
	}
	printf("\n");
}

int main() {
	int n;			// Vector size
	double *vec;
	int blocks = 256, threads = 256;

	// Set up initial data
	scanf("%d", &n);
	vec = (double *)malloc(sizeof(double) * n);

	for (int i = 0; i < n; ++i) {
		scanf("%lf", &vec[i]);
	}

	// Create CUDA vectors and copy data to first
	double *devVec, *revVec;

	CSC(cudaMalloc(&devVec, sizeof(double) * n));
	CSC(cudaMalloc(&revVec, sizeof(double) * n));
	CSC(cudaMemcpy(devVec, vec, sizeof(double) * n, cudaMemcpyHostToDevice));

	// Call kernel
	kernel<<<blocks, threads>>>(devVec, revVec, n);
	CSC(cudaGetLastError());

	// Copy results from device to host memory
	CSC(cudaMemcpy(vec, revVec, sizeof(double) * n, cudaMemcpyDeviceToHost));
	CSC(cudaFree(devVec));
	CSC(cudaFree(revVec));

	// Print results
	for (int i = 0; i < n; ++i) {
		printf("%.10e ", vec[i]);
	}

	free(vec);

	return 0;
}
