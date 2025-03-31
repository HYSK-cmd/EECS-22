/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* Movie.c: source file for basic movie manipulations                */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"
#include <stdio.h>

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
Movie *CreateMovie(void)
{
	Movie *movie = malloc(sizeof(Movie));
	if(!movie){
		perror("Out of Memory. Aborting..");
		exit(10);
	}
	movie->Frames = CreateImageList();
	return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(Movie *movie)
{
	assert(movie);
	if (movie->Frames) {
    	DeleteImageList(movie->Frames);
		movie->Frames = NULL; 
    }
	free(movie);
}
int clip(int value){
	if (value < 0) return 0;
	if (value > 255) return 255;
	return value;
}
/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(Movie *movie)
{
	if (!movie) {
        printf("Error: NULL movie pointer passed to YUV2RGBMovie.\n");
        return;
    }
	IENTRY *Entry = movie->Frames->First;
	while(Entry){
		assert(Entry);
		YUVImage *yuvImage = (YUVImage *)(Entry->image);
		if (!yuvImage) {
            Entry = Entry->Next;
            continue;
        }
		int WIDTH = yuvImage->W;
		int HEIGHT = yuvImage->H;
		Image *img = CreateImage(WIDTH, HEIGHT);
		for(int i = 0; i < WIDTH; i++){
			for(int j = 0; j < HEIGHT; j++){
				unsigned int C = GetPixelY(yuvImage, i, j) - 16;
				unsigned int D = GetPixelU(yuvImage, i, j) - 128;
				unsigned int E = GetPixelV(yuvImage, i, j) - 128;

				unsigned int R = clip((298 * C + 409 * E + 128) >> 8);
				unsigned int G = clip((298 * C - 100 * D - 208 * E + 128) >> 8);
				unsigned int B = clip((298 * C + 516 * D + 128) >> 8);
				SetPixelR(img, i, j, R);
				SetPixelG(img, i, j, G);
				SetPixelB(img, i, j, B);
			}
		}
		if (Entry->image) {
            DeleteYUVImage((YUVImage*)(Entry->image));
        }
        Entry->image = img;
        Entry = Entry->Next;
	}
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(Movie *movie)
{
	if (!movie) {
        printf("Error: NULL movie pointer passed to RGB2YUVMovie.\n");
        return;
    }

	IENTRY *Entry = movie->Frames->First;
	
	while(Entry){
		assert(Entry);
		Image *img = (Image *)(Entry->image);
		int WIDTH = img->W;
		int HEIGHT = img->H;
		YUVImage *yuvimg = CreateYUVImage(WIDTH, HEIGHT);
		for(int i = 0; i < WIDTH; i++){
			for(int j = 0; j < HEIGHT; j++){
				unsigned int Y = clip((( 66 * GetPixelR(img, i, j)
				+ 129 * GetPixelG(img, i, j)
				+ 25 * GetPixelB(img, i, j) + 128) >> 8) + 16);
				unsigned int U = clip((( -38 * GetPixelR(img, i, j) 
				- 74 * GetPixelG(img, i, j) 
				+ 112 * GetPixelB(img, i, j) + 128) >> 8) + 128);
				unsigned int V = clip((( 112 * GetPixelR(img, i, j) 
				- 94 * GetPixelG(img, i, j) 
				- 18 * GetPixelB(img, i, j) + 128) >> 8) + 128);
				SetPixelY(yuvimg, i, j, Y);
				SetPixelU(yuvimg, i, j, U);
				SetPixelV(yuvimg, i, j, V);
			}
		}
		if (Entry->image) {
			DeleteImage((Image*)(Entry->image));
        }
		Entry->image = yuvimg;
		Entry = Entry->Next;
		
	}
}
/* EOF */
