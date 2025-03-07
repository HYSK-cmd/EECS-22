/*****************************************************/
/* PhotoLabTest.c: Test program file       		         */
/*****************************************************/
#define  DEBUG      // Enable DEBUG mode
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Constants.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], 
			  unsigned char G[WIDTH][HEIGHT], 
			  unsigned char B[WIDTH][HEIGHT]);
int main() {
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];
    
    AutoTest(R, G, B);
    printf("AutoTest completed.\n");
	return 0;
}
// AutoTest implementation
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
	char fname[SLEN] = "EngPlaza";
	char sname[SLEN];

	LoadImage(fname, R, G, B);
	Negative(R, G, B);
	strcpy(sname, "negative");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("Negative tested!\n\n");
    #endif

	LoadImage(fname, R, G, B);
	ColorFilter(R, G, B, 130, 130, 150, 30, 0, 255, 255);
	strcpy(sname, "colorfilter");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("Color Filter tested!\n\n");
    #endif

	LoadImage(fname, R, G, B);
	Edge(R, G, B);
	strcpy(sname, "edge");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("Edge Detection tested!\n\n");
    #endif

	LoadImage(fname, R, G, B);
	HMirror(R, G, B);
	strcpy(sname, "hmirror");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("HMirror tested!\n\n");
    #endif

	LoadImage(fname, R, G, B);
	AddBorder (R, G, B, "pink", 32);
	strcpy(sname, "border");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("Border tested!\n\n");
    #endif

	LoadImage(fname, R, G, B);
	BlackNWhite(R, G, B);
	strcpy(sname, "bw");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("Black & White tested!\n\n");
    #endif

	LoadImage(fname, R, G, B);
	VFlip(R, G, B);
	strcpy(sname, "vflip");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("HFlip tested!\n\n");
    #endif

	LoadImage(fname, R, G, B);
	Shuffle(R, G, B);
	strcpy(sname, "shuffle");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("Shuffle tested!\n\n");
	#endif

	LoadImage(fname, R, G, B);
	FishEye(R, G, B, 0.5, 1.5, 0.5);
	strcpy(sname, "fisheye");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("Fisheye tested!\n\n");
	#endif
	
	LoadImage(fname, R, G, B);
	Posterize(R, G, B, 7, 7, 7) ;
	strcpy(sname, "posterize");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("Posterize tested!\n\n");
	#endif

	LoadImage(fname, R, G, B);
	Rotate(R, G, B, 22, 0.78, 110, 220);
	strcpy(sname, "rotate");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("Rotate tested!\n\n");
    #endif
	
	LoadImage(fname, R, G, B);
	MotionBlur(40, R, G, B) ;
	strcpy(sname, "blur");
	SaveImage(sname, R, G, B);
    #ifdef DEBUG
	printf("MotionBlur tested!\n\n");
	#endif
}
/* EOF PhotoLabTest.c */