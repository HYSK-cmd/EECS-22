#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Image.h"
/* Get the (R, G, B) intensity of pixel (x, y) in image */
unsigned char GetPixelR(const Image *image, unsigned int x,  unsigned int y){
    return image->R[x + y * image->W]; //image->W same as (*image).W
}
unsigned char GetPixelG(const Image *image, unsigned int x,  unsigned int y){
    return image->G[x + y * image->W];
}
unsigned char GetPixelB(const Image *image, unsigned int x,  unsigned int y){
    return image->B[x + y * image->W];
}

/* Set the color intensity of the (Red, Green, Blue) channel of pixel (x, y) in image to (r, g, b) */
void SetPixelR(Image *image, unsigned int x,  unsigned int y, unsigned char r){
    image->R[x + y * image->W] = r;
}
void SetPixelG(Image *image, unsigned int x,  unsigned int y, unsigned char g){
    image->G[x + y * image->W] = g;
}
void SetPixelB(Image *image, unsigned int x,  unsigned int y, unsigned char b){
    image->B[x + y * image->W] = b;
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const Image *image){
    return image->W;
}
/* Return the image's height in pixels */
unsigned int ImageHeight(const Image *image){
    return image->H;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
Image *CreateImage(unsigned int Width, unsigned int Height){
    Image *image =(Image *)malloc(sizeof(Image));
    if (Width == 0 || Height == 0) {
        fprintf(stderr, "Error: Invalid image dimensions %u x %u\n", Width, Height);
        return NULL;
    }
    if(image == NULL){
        assert("The input pointer is invalid");
        return NULL;
    }

    image->W = Width;
    image->H = Height;

    image->R = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    image->G = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    image->B = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));

    if(image->R == NULL || image->G == NULL || image->B == NULL){
        assert("Failed to allocate memory for image");
        DeleteImage(image);
        return NULL;
    }
    return image;
}

/* Free the memory for the R/G/B values and Image structure */
void DeleteImage(Image *image){
    assert(image);
    free(image->R);
    free(image->G);
    free(image->B);
    free(image);
}
