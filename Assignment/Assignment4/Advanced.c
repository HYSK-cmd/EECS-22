#include "Advanced.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
/* Crop */
Image *Crop(Image *image, int x, int y, int W, int H){
    // Allocate dynamic memory for cropped_Img
    assert(image != NULL && "Error: invalid input image.\n");
    Image *cropped_Img = (Image *)malloc(sizeof(Image));

    // Assign new W,H,R,G,B
    cropped_Img->W = W;
    cropped_Img->H = H;
    cropped_Img->R = (unsigned char *)malloc(W * H * sizeof(unsigned char));
    cropped_Img->G = (unsigned char *)malloc(W * H * sizeof(unsigned char));
    cropped_Img->B = (unsigned char *)malloc(W * H * sizeof(unsigned char));

    // Copy RGB values from the original image to cropped_Img
    for(int i = 0; i < W; i++){
        for(int j = 0; j < H; j++){
            SetPixelR(cropped_Img, i, j, GetPixelR(image, x+i, y+j));
            SetPixelG(cropped_Img, i, j, GetPixelG(image, x+i, y+j));
            SetPixelB(cropped_Img, i, j, GetPixelB(image, x+i, y+j));
        }
    }

    // Free the original image
    DeleteImage(image);
    return cropped_Img;
}

/* Resize */
Image *Resize(Image *image, int newWidth, int newHeight){
    double scaleX, scaleY;
    // Allocate dynamic memory for cropped_Img
    assert(image != NULL && "Error: invalid input image.\n");
    Image *resized_Img = (Image *)malloc(sizeof(Image));

    // Get W,H from both the original and new image structures
    int imageWidth = image->W;
    int imageHeight = image->H;
    resized_Img->W = newWidth;
    resized_Img->H = newHeight;

    // Calculate scaleX and scaleY
    scaleX = (double)newWidth / imageWidth;
    scaleY = (double)newHeight / imageHeight;

    resized_Img->R = (unsigned char *)malloc(newWidth * newHeight * sizeof(unsigned char));
    resized_Img->G = (unsigned char *)malloc(newWidth * newHeight * sizeof(unsigned char));
    resized_Img->B = (unsigned char *)malloc(newWidth * newHeight * sizeof(unsigned char));

    // Copy RGB values from the original image to resized_Img
    for(int x = 0; x < newWidth; x++){
        for(int y = 0; y < newHeight; y++){
            // matrix calculation
            int dx = (int)(x / scaleX);
            int dy = (int)(y / scaleY);
            // Iterate over the target image to work both enlarging and shrinking image 
            SetPixelR(resized_Img, x, y, GetPixelR(image, dx, dy));
            SetPixelG(resized_Img, x, y, GetPixelG(image, dx, dy));
            SetPixelB(resized_Img, x, y, GetPixelB(image, dx, dy));
        }
    }
    // Free the original image
    DeleteImage(image);
    return resized_Img;
}

/* Watermark */
Image *Watermark(Image *image, const Image *watermark_image){
    // Get W,H from both the original and watermark image
    assert(image != NULL && "Error: invalid input image.\n");
    int Width = image->W, Height = image->H;
    int watermark_W = watermark_image->W;
    int watermark_H = watermark_image->H;
    double factor = 1.45;

    for(int i = 0; i < Width; i++){
        for(int j = 0; j < Height; j++){
            // Wrap around the original image in case the images are of different sizes
            int x = i % watermark_W;
            int y = j % watermark_H;

            // If R, G, and, B value is 0 at x,y position
            if((GetPixelR(watermark_image, x, y) == 0) && (GetPixelG(watermark_image, x, y) == 0) && 
            (GetPixelB(watermark_image, x, y) == 0)){
                // Multiply them with the factor
                int r = GetPixelR(image, i, j) * factor;
                int g = GetPixelG(image, i, j) * factor;
                int b = GetPixelB(image, i, j) * factor;
                
                // Use saturated arithmetic to prevent an overflow
                if(r > 255) r = 255;
                if(g > 255) g = 255;
                if(b > 255) b = 255;

                // Set RGB values to the image
                SetPixelR(image, i, j, r);
                SetPixelG(image, i, j, g);
                SetPixelB(image, i, j, b);
                
            }
        }
    }
    return image;
}

/* Rotate by 90 */
Image *RotateBy90(Image *image, int rotateDirection){
    // Allocate dynamic memory for rotate_Img
    assert(image != NULL && "Error: invalid input image.\n");
    Image *rotate_Img = (Image *)malloc(sizeof(Image));
    
    // Swap height and width
    rotate_Img->W = image->H;
    rotate_Img->H = image->W;
    int Width = rotate_Img->W, Height = rotate_Img->H;

    rotate_Img->R = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    rotate_Img->G = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    rotate_Img->B = (unsigned char *)malloc(Width * Height * sizeof(unsigned char));
    
    // If rotated clockwise
    if(rotateDirection == 0){
        for(int i = 0; i < Height; i++){
            for(int j = 0; j < Width; j++){
                // Starting from the top right corner because that's where the starting point in original image is at
                SetPixelR(rotate_Img, Width - 1 - j, i, GetPixelR(image, i, j));
                SetPixelG(rotate_Img, Width - 1 - j, i, GetPixelG(image, i, j));
                SetPixelB(rotate_Img, Width - 1 - j, i, GetPixelB(image, i, j));
            }
        }
    } else if (rotateDirection == 1){
        for(int i = 0; i < Width; i++){
            for(int j = 0; j < Height; j++){
                // Starting from the bottom left because that's where the starting point in orignal image is at
                SetPixelR(rotate_Img, i, j, GetPixelR(image, Height - 1 - j, i));
                SetPixelG(rotate_Img, i, j, GetPixelG(image, Height - 1 - j, i));
                SetPixelB(rotate_Img, i, j, GetPixelB(image, Height - 1 - j, i));
            }
        }
    } else {
        // If the option is neither 0 nor 1
        printf("Invalid value for rotate option.\n");
        return NULL;
    }
    // Free the image
    DeleteImage(image);
    return rotate_Img;
}