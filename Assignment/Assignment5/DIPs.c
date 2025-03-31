/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* DIPs.c: source file for DIP operations                            */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "DIPs.h"
#include "Constants.h"
#include "string.h"
#include "math.h"

/* Black and White */
Image *BlackNWhite(Image *image)
{
	assert(image);
	int x, y, tmp;

	for (y = 0; y < ImageHeight(image); y++) {
		for (x = 0; x < ImageWidth(image); x++) {
		tmp = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
			SetPixelR(image, x, y, tmp);
			SetPixelG(image, x, y, tmp);
			SetPixelB(image, x, y, tmp);
		}
	}
	return image;
}

/* Mirror image horizontal  */
Image *HMirror(Image *image) {
	assert(image);
	int x, y;
	for (y = 0; y < ImageHeight(image); y++) {
		for (x = 0; x < ImageWidth(image)/2; x++) {
			SetPixelG(image, ImageWidth(image) - 1 - x, y, GetPixelG(image, x, y));
			SetPixelB(image, ImageWidth(image) - 1 - x, y, GetPixelB(image, x, y));
			SetPixelR(image, ImageWidth(image) - 1 - x, y, GetPixelR(image, x, y));
		}
	}
	return image;
}

/* Edge detection */
Image *Edge(Image *image) {
	assert(image);
	Image *tmpImage = CreateImage(ImageWidth(image), ImageHeight(image));
	assert(tmpImage);

	int x, y, m, n;
	memcpy(tmpImage->R, image->R, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
	memcpy(tmpImage->G, image->G, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
	memcpy(tmpImage->B, image->B, ImageWidth(image) * ImageHeight(image) * sizeof(unsigned char));
	for (y = 1; y < ImageHeight(image) - 1; y++) {
		for (x = 1; x < ImageWidth(image) - 1; x++) {
			int tmpR = 0;
			int tmpG = 0;
			int tmpB = 0;
			for (m = -1; m <= 1; m++) {
				for (n = -1; n <= 1; n++) {
					tmpR += (GetPixelR(tmpImage, x, y) - GetPixelR(tmpImage, x + n, y + m));
					tmpG += (GetPixelG(tmpImage, x, y) - GetPixelG(tmpImage, x + n, y + m));
					tmpB += (GetPixelB(tmpImage, x, y) - GetPixelB(tmpImage, x + n, y + m));
				}
			}
			SetPixelR(image, x, y, (tmpR > 255) ? 255 : (tmpR < 0) ? 0 : tmpR);
			SetPixelG(image, x, y, (tmpG > 255) ? 255 : (tmpG < 0) ? 0 : tmpG);
			SetPixelB(image, x, y, (tmpB > 255) ? 255 : (tmpB < 0) ? 0 : tmpB);
		}
	}
	for (y = 0; y < ImageHeight(image); y++) {
		x = 0;
		SetPixelR(image, x, y, 0);
		SetPixelG(image, x, y, 0);
		SetPixelB(image, x, y, 0);
		x = ImageWidth(image) - 1;
		SetPixelR(image, x, y, 0);
		SetPixelG(image, x, y, 0);
		SetPixelB(image, x, y, 0);
	}
	for (x = 0; x < ImageWidth(image); x++) {
		y = 0;
		SetPixelR(image, x, y, 0);
		SetPixelG(image, x, y, 0);
		SetPixelB(image, x, y, 0);
		y = ImageHeight(image) - 1;
		SetPixelR(image, x, y, 0);
		SetPixelG(image, x, y, 0);
		SetPixelB(image, x, y, 0);
	}
	DeleteImage(tmpImage);
	tmpImage = NULL;
	return image;
}

/* Add a watermark to an image */
Image *Watermark(Image *image, const Image *watermark,
	 unsigned int topLeftX, unsigned int topLeftY)
{
	// Get W,H from both the original and watermark image
    assert(image != NULL && "Error: invalid input image.\n");
    int Width = image->W, Height = image->H;
	int watermark_w = watermark->W, watermark_h = watermark->H;
    double factor = 1.45;
	
    for(int i = 0; i < watermark_w; i++){
        for(int j = 0; j < watermark_h; j++){
			if(topLeftX + i < Width && topLeftY + j < Height){
				// initialize random starting coordinates
				int x = i + topLeftX;
				int y = j + topLeftY;
				// If R, G, and, B value is 0 at x,y position
				if((GetPixelR(watermark, i, j) == 0) && (GetPixelG(watermark, i, j) == 0) && 
				(GetPixelB(watermark, i, j) == 0)){
					// Multiply them with the factor
					int r = GetPixelR(image, x, y) * factor;
					int g = GetPixelG(image, x, y) * factor;
					int b = GetPixelB(image, x, y) * factor;
					
					// Use saturated arithmetic to prevent an overflow
					if(r > 255) r = 255;
					if(g > 255) g = 255;
					if(b > 255) b = 255;

					// Set RGB values to the image
					SetPixelR(image, x, y, r);
					SetPixelG(image, x, y, g);
					SetPixelB(image, x, y, b);
				}
            }
        }
    }
    return image;
}

/* Spotlight */
Image *Spotlight(Image *image, int centerX, int centerY, unsigned int radius)
{
	assert(image);
	int Width = image->W, Height = image->H;
	float max_radius = sqrt(pow((float)Width/2, 2) + pow((float)Height/2, 2));
	if(max_radius < radius){
		radius = max_radius;
	}
	for(int i = 0; i < Width; i++){
		for(int j = 0; j < Height; j++){
			float circle = sqrt(pow((i-centerX), 2) + pow((j-centerY), 2));
			if (circle > radius) { // set any pixels outside the radius to black
                SetPixelR(image, i, j, 0);
                SetPixelG(image, i, j, 0);
                SetPixelB(image, i, j, 0);
            }
		}
	}
	return image;
}

/* Rotate and zoom an image */
Image *Rotate(Image *image, double Angle, double ScaleFactor)
{
	assert(image);
	const double PI = 3.141592653589793;
	double rad = Angle * (PI / 180);

	int Width = image->W, Height = image->H;
	int CenterX = Width / 2, CenterY = Height / 2;
	Image *rotateimg = CreateImage(Width, Height);

	for(int x = 0; x < Width; x++){
		for(int y = 0; y < Height; y++){
			int dx = (int)((((cos(rad) / ScaleFactor) * (x - CenterX)) + ((sin(rad) / ScaleFactor) * (y - CenterY))) + CenterX);
			int dy = (int)((((-sin(rad) / ScaleFactor) * (x - CenterX)) + ((cos(rad) / ScaleFactor) * (y - CenterY))) + CenterY);
			if((dx >= 0 && dx < Width) && (dy >= 0 && dy < Height)){
				SetPixelR(rotateimg, x, y, GetPixelR(image, dx, dy));
				SetPixelG(rotateimg, x, y, GetPixelG(image, dx, dy));
				SetPixelB(rotateimg, x, y, GetPixelB(image, dx, dy));
			} else { //set outside the image to black
				SetPixelR(rotateimg, x, y, 0);
				SetPixelG(rotateimg, x, y, 0);
				SetPixelB(rotateimg, x, y, 0);
			}
		}
	}
	return rotateimg;
}

/* EOF */