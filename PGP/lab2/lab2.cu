#include <stdio.h>
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

typedef struct _image {
    int width;
    int height;
    uchar4* pixels;
} image;

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

texture<uchar4, 2, cudaReadModeElementType> tex;

__device__ __host__ int pos(int i, int border) {
    return max(min(i, border), 0);
}

__global__ void gaussianBlurKernel(uchar4* pixels,
                                   int rad,
                                   float div,
                                   int width,
                                   int height,
                                   int axisX,
                                   int axisY) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    int idy = blockDim.y * blockIdx.y + threadIdx.y;
    int offsetX = blockDim.x * gridDim.x;
    int offsetY = blockDim.y * gridDim.y;

    int i, j, k;
    uchar4 pixel;

    for (i = idx; i < width; i += offsetX) {
        for (j = idy; j < height; j += offsetY) {
            float r = 0.0,
                  g = 0.0,
                  b = 0.0;

            float weight = 0.0;

            for (k = -rad; k <= rad; k++) {
                weight = exp(-(float)(k * k) / (float)(2 * rad * rad));
                
                int posX = pos(i + (k * axisX), width);
                int posY = pos(j + (k * axisY), height);

                pixel = tex2D(tex, (float)posX, (float)posY);

                r += (pixel.x) * weight;
                g += (pixel.y) * weight;
                b += (pixel.z) * weight;
            }

            pixels[i + j * width] = make_uchar4((unsigned char)(r / div),
                               (unsigned char)(g / div),
                               (unsigned char)(b / div),
                               (float)0.0);
        }
    }
}

void printPixels(uchar4* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << (float)arr[i].x << " " << (float)arr[i].y << " " << (float)arr[i].z << std::endl;
    }
}

int main(int argc, char* argv[]) {
    int r;                  // Filter radius
    char srcFilename[256];
    char resFilename[256];
    
    dim3 gridSize(32, 32);
    dim3 blockSize(32, 32);

    scanf("%s", srcFilename);
    scanf("%s", resFilename);
    scanf("%d", &r);

    image* img = readImage(srcFilename);

    cudaArray *cudaArr;
    cudaChannelFormatDesc channel = cudaCreateChannelDesc<uchar4>();
    CSC(cudaMallocArray(&cudaArr, &channel, img->width, img->height));
    CSC(cudaMemcpyToArray(cudaArr, 0, 0, img->pixels,
        sizeof(uchar4) * img->height * img->width, cudaMemcpyHostToDevice));

    tex.addressMode[0] = cudaAddressModeClamp;
    tex.addressMode[1] = cudaAddressModeClamp;
    tex.channelDesc = channel;
    tex.filterMode = cudaFilterModePoint;
    tex.normalized = false;

    cudaBindTextureToArray(tex, cudaArr, channel);

    uchar4* tmpData;
    cudaMalloc(&tmpData, sizeof(uchar4) * img->height * img->width);

    if (r > 0) {
        float div = 0.0;
        
        for (int i = -r; i <= r; i++) {
            div += exp(-(float)(i * i) / (float)(2 * r * r));
        }

        gaussianBlurKernel<<<gridSize, blockSize>>>(tmpData, r, div, img->width, img->height, 1, 0);
        CSC(cudaGetLastError());

        CSC(cudaDeviceSynchronize());

        CSC(cudaMemcpy(img->pixels, tmpData, sizeof(uchar4) * img->height * img->width, cudaMemcpyDeviceToHost));
        CSC(cudaMemcpyToArray(cudaArr, 0, 0, img->pixels, sizeof(uchar4) * img->height * img->width, cudaMemcpyHostToDevice));

        gaussianBlurKernel<<<gridSize, blockSize>>>(tmpData, r, div, img->width, img->height, 0, 1);
        CSC(cudaGetLastError());

        CSC(cudaDeviceSynchronize());

        CSC(cudaMemcpy(img->pixels, tmpData, sizeof(uchar4) * img->height * img->width, cudaMemcpyDeviceToHost));
        // printPixels(img->pixels, img->height * img->width);
    }

    writeImage(resFilename, img);

    CSC(cudaUnbindTexture(tex));
    CSC(cudaFreeArray(cudaArr));
    CSC(cudaFree(tmpData));

    deleteImage(img);

    return 0;
}