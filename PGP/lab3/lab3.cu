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

#define DIM 3
#define R 0
#define G 1
#define B 2

typedef _pxlClass {
    int size;
    int* x;
    int* y;
    double avg[DIM];
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

pxlClass* readPxlClasses(int nc, image* img) {
    pxlClass* pxlC = (pxlClass *)malloc(sizeof(pxlClass * nc));
    
    for (int i = 0; i < nc; ++i) {
        int np;

        scanf("%d", np);

        pxlC[i].x = (int *)malloc(sizeof(int) * np);
        pxlC[i].y = (int *)malloc(sizeof(int) * np);

        memset(pxlC[i].avg, 0.0, sizeof(pxlC[i].avg));
        
        for (int j = 0; j < np; ++j) {
            scanf("%d %d", &(pxlC[i].x[j]), &(pxlC[i].y[j]));

            uchar4 pixel = img->pixels[pos2Dto1D(pxlC[i].x[j], pxlC[i].y[j], img->width)];

            pxlC[i].avg[R] += pixel.x;
            pxlC[i].avg[G] += pixel.y;
            pxlC[i].avg[B] += pixel.z;
        }

        pxlC[i].avg[R] /= (double)np;
        pxlC[i].avg[G] /= (double)np;
        pxlC[i].avg[B] /= (double)np;
    }

    return pxlC;
}

int main(int argc, char** argv) {
    char srcFilename[256];
    char resFilename[256];
    int nc;

    scanf("%s", srcFilename);
    scanf("%s", resFilename);

    image *img = readImage(srcFilename);

    scanf("%d", nc);
    pxlClass* pxlC = readClasses(nc, img);

    uchar4* res = (uchar4 *)malloc(sizeof(uchar4) * img->height * img->width);
    memcpy(res, img->pixels, sizeof(uchar4) * img->height * img->width);

    // TODO Main algorithm

    return 0;
}