#include <stdio.h>

#define CSC(call) \
do { \
	cudaError_t res = call; \
	if (res != cudaSuccess) { \
		fprintf(stderr, "ERROR: file:%s line:%d message:%s\n", \
				__FILE__, __LINE__, cudaGetErrorString(res)); \
		exit(0); \
	} \
} while (0)

typedef struct image {
    int w;
    int h;
    uchar4* data;
} image;

image* readImage(const char* filename) {
    image* img = (image *)malloc(sizeof(image));
    
    FILE* input = fopen(filename, "rb");

    fread(&img->w, sizeof(img->w), 1, input);
    fread(&img->h, sizeof(img->h), 1, input);
    
    img->data = (uchar4 *)malloc(sizeof(uchar4) * img->h * img->w);
    fread(&img->data, sizeof(img->data), img->h * img->w, input);

    fclose(input);

    return img;
}

void writeImage(char* filename, image* img) {
    FILE* output = fopen(filename, "wb");

    fwrite(&img->w, sizeof(img->w), 1, output);
    fwrite(&img->h, sizeof(img->h), 1, output);
    fwrite(&img->data, sizeof(img->data), img->h * img->w, output);

    fclose(output);
}

void deleteImage(image* img) {
    free(img->data);
    free(img);
    img = NULL;
}

__global__ void gaussianBlurKernel(uchar4* data,
                                   int r,
                                   float div,
                                   int w,
                                   int h,
                                   int axisX,
                                   int axisY) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int idy = blockDim.y * blockIdx.y + threadIdx.y;
    int offsetX = blockDim.x * gridDim.x;
    int offsetY = blockDim.y * gridDim.y;

    int i, j, k;
    uchar4 pxl;

    for (i = idx; i < w, i += offsetX) {
        for (j = idy; j < h, j += offsetY) {
            float r = 0.0,
                  g = 0.0,
                  b = 0.0;

            float weight = 0.0;

            for (k = -r; k <= r; k++) {
                weight = exp((float)-(k * k) / (float)(2 * r * r));
                
                int posX = pos(i + (k * axisX), w);
                int posY = pos(j + (k * axisY), h);

                pxl = tex2D(tex, (float)posX, (float)posY);

                r += (p.x) * weight;
                g += (p.y) * weight;
                b += (p.z) * weight;
            }

            data = make_uchar4((unsigned char)(r / div),
                               (unsigned char)(g / div),
                               (unsigned char)(b / div),
                               (float)0.0);
        }
    }
}

__device__ __host__ int pos(int i, int border) {
    return max(0, min(i, border));
}

texture <uchar4, 2, cudaReadModeElementType> tex;

int main(int argc, char* argv[]) {
    int r;                  // Filter radius
    char srcFilename[256];
    char resFilename[256];

    scanf("%s", srcFilename);
    scanf("%s", resFilename);
    scanf("%d", r);

    image* img = readImage(srcFilename);

    cudaArray *cuArr;
    cudaChannelFormatDesc channel = cudaCreateChannelDesc<uchar4>();
    CSC(cudaMallocArray(&cuArr, &channel, img->w, img->h));
    CSC(cudaMemcpyToArray(cuArr, 0, 0, img->data, sizeof(uchar4) * img->h * img->w, cudaMemcpyHostToDevice));

    tex.addressMode[0] = cudaAddressModeClamp;
    tex.addressMode[1] = cudaAddressModeClamp;
    tex.channelDesc = channel;
    tex.filterMode = cudaFilterModePoint;
    tex.normalized = false;

    dim3 gridSize(32, 32);
    dim3 blockSize(32, 32);

    cudaBindTextureToArray(tex, cuArr, channel);
    uchar4* tmpData;
    cudaMalloc(&tmpData, sizeof(uchar4) * img->h * img->w);

    if (r > 0) {
        float div = 0.0;
        
        for (int i = -r; i <= r; i++) {
            div += exp((float)-(i * i) / (float)(2 * r * r));
        }

        gaussianBlurKernel<<<gridSize, blockSize>>>(tmpData, r, div, img->w, img->h, 1, 0);
        CSC(cudaGetLastError());

        CSC(cudaDeviceSynchronize());

        CSC(cudaMemcpy(img->data, tmpData, sizeof(uchar4) * img->h * img->h, cudaMemcpyDeviceToHost));
        CSC(cudaMemcpyToArray(cuArr, 0, 0, img->data, sizeof(uchar4) * img->h * img->w, cudaMemcpyHostToDevice));

        gaussianBlurKernel<<<gridSize, blockSize>>>(tmpData, r, div, img->w, img->h, 0, 1);
        CSC(cudaGetLastError());

        CSC(cudaDeviceSynchronize());

        CSC(cudaMemcpy(img->data, tmpData, sizeof(uchar4) * img->h * img->w, cudaMemcpyDeviceToHost));
    }

    writeImage(resFilename, img);

    CSC(cudaUnbindTexture(tex));
    CSC(cudaFreeArray(cuArr));
    CSC(cudaFree(tmpData));

    deleteImage(img);

    return 0;
}