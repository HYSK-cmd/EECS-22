#include "Constants.h"
#include "FileIO.h"
#include "Test.h"
#include "DIPs.h"
#include "Advanced.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void PrintMenu();

int main(void){
	/* user input option */
	int option;		
	/* input file name */	
	char fname[SLEN];		

	Image *image = NULL;
	#ifdef DEBUG
		AutoTest();
		return 0;
	#endif

	PrintMenu();
	printf("Please make your choice: ");
	scanf("%d", &option);

	/* return code of LoadImage() */
	int r24 = -1;
	/* return code of Autotest() */
	int rc;

	/* ColorFilter() parameters */
	int target_r, target_g, target_b, threshold;
	double factor_r, factor_g, factor_b;
	/* Pixelate() parameter */
	int block_Size;
	/* AddBorder() parameter */
	int border_width;
	char colorOption[SLEN];
	/* Crop() parameters */
	int x_offset, y_offset, crop_W, crop_H;
	/* Resize() parameters */
	int resize_W, resize_H;
	/* Shift() parameters */
	int shift_X = 160, shift_Y = 40;
	/* RotateBy90() parameter */
	int rotateDir;

	while (option != EXIT) {
		if (option == 1) {
			printf("Please input the file name to load: ");
			scanf("%75s", fname);
			image = LoadImage(fname);
			if (!image) {
				printf("Error: Failed to load image %s\n", fname);
			} else {
				printf("\"%s.ppm\" loaded Successfully", fname);
				r24 = SUCCESS;
			}
		}
		/* menu item 2 - 16 requires image is loaded first */
		else if (option >= 2 && option <= 17) {
			if (r24 != SUCCESS)	 {
				printf("No image is read.\n");
			}
			/* now image is loaded */
			else {
				switch(option) {
					case 2:
						printf("Please input the file name to save: ");
						scanf("%75s", fname);
						SaveImage(fname, image);
						printf("Image saved successfully.\n");
						if (image != NULL) {
							DeleteImage(image);
							image = NULL;
						}
						break;
					case 3:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							image = BlackNWhite(image);
							printf("\"Black & White\" operation is done!\n");
						}
						break;
					case 4:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							image = Negative(image);
							printf("\"Negative\" operation is done!\n");
						}
						break;
					case 5:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							printf("Enter Red   component for the target color: ");
							scanf("%d", &target_r);
							printf("Enter Green component for the target color: ");
							scanf("%d", &target_g);
							printf("Enter Blue  component for the target color: ");
							scanf("%d", &target_b);
							printf("Enter threshold for the color difference: ");
							scanf("%d", &threshold);
							printf("Enter value for Red component in the target color: ");
							scanf("%lf", &factor_r);
							printf("Enter value for Green component in the target color: ");
							scanf("%lf", &factor_g);
							printf("Enter value for Blue  component in the target color: ");
							scanf("%lf", &factor_b);
							image = ColorFilter(image, target_r, target_g, target_b, threshold, factor_r, factor_g, factor_b);
							printf("\"Color Filter\" operation is done!\n");
						}
						break;
					case 6:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							image = Edge(image);
							printf("\"Edge\" operation is done!\n");
						}
						break;
					case 7:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							image = Shuffle(image);
							printf("\"Shuffle\" operation is done!\n");
						}
						break;
					case 8:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							image = VFlip(image);
							printf("\"VFlip\" operation is done!\n");
						}
						break;
					case 9:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							image = HMirror(image);
							printf("\"HMirror\" operation is done!\n");
						}
						break;
					case 10:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							printf("Enter border width: ");
							scanf("%d", &border_width);
							printf("Available border colors : black, white, red, green, blue, yellow, cyan, pink, orange\n");
							printf("Select border color from the options: ");
							scanf("%s",colorOption);
							image = AddBorder(image, colorOption, border_width);
							printf("\"Border\" operation is done!\n");
						}
						break;
					case 11:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							printf("Enter block size: ");
                			scanf("%d", &block_Size);
							image = Pixelate(image, block_Size);
							printf("\"Pixelate\" operation is done!\n");
						}
						break;
					case 12:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							image = Shift(image, shift_X, shift_Y);
							printf("\"Shift\" operation is done!\n");
						}
						break;
					case 13:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							printf("Please enter the X offset value: ");
							scanf("%d", &x_offset);
							printf("Please enter the Y offset value: ");
							scanf("%d", &y_offset);
							printf("Please input the crop width: ");
							scanf("%d", &crop_W);
							printf("Please input the crop height: ");
							scanf("%d", &crop_H);
							image = Crop(image, x_offset, y_offset, crop_W, crop_H);
							printf("\"Crop\" operation is done!\n");
						}
						break;
					case 14:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							printf("Please input the new image width: ");
							scanf("%d", &resize_W);
							printf("Please input the new image height: ");
							scanf("%d", &resize_H);
							image = Resize(image, resize_W, resize_H);
							printf("\"Resizing the image\" operation is done!\n");
						}
						break;
					case 15:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							// Load the watermark image first
							char fname[SLEN] = "watermark_template";
							Image *watermark = LoadImage(fname);
							image = Watermark(image, watermark);
							// Free the image
							DeleteImage(watermark);
							printf("\"Watermark\" operation is done!\n");
						}
						break;
					case 16:
						if(image == NULL){
							printf("No image to process!\n");
						} else {
							printf("Please input the direction of rotation (0:clockwise, 1:counterclockwise): ");
							scanf("%d", &rotateDir);
							image = RotateBy90(image, rotateDir);
							printf("\"RotateBy90\" operation is done!\n");
						}
						break;
					case 17:
						rc = AutoTest();
						if(rc != 0){
							// return an error code
							printf("AutoTest failed, error code %d.\n", rc);
						} else {
							r24 = SUCCESS; 
							printf("AutoTest finished successfully.\n");
							DeleteImage(image);
						}
						break;
					default:
						break;
				}
			}
		}
		else if (option == 18) {
			break;
		} 
		else {
			printf("Invalid selection!\n");
		}
		/* Process finished, waiting for another input */
		PrintMenu();
		printf("Please make your choice: ");
		scanf("%d", &option);
	}
	//Free the image before exiting the program.
	printf("You exit the program.\n");
	return 0;
}

void PrintMenu() {
	printf("\n----------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save an image in PPM and JPEG format\n");
	printf(" 3: Change a color image to Black & White\n");
	printf(" 4: Make a negative of an image\n");
	printf(" 5: Color filter an image\n");
	printf(" 6: Sketch the edge of an image\n");
	printf(" 7: Shuffle an image\n");
	printf(" 8: Flip an image vertically\n");
	printf(" 9: Mirror an image horizontally\n");
	printf("10: Add border to an image\n");
	printf("11: Pixelate an image\n");
	printf("12: Shift an image\n");
	printf("13: Crop an image\n");
	printf("14: Resize an image\n");
	printf("15: Add Watermark to an image\n");
	printf("16: Rotate an image by 90 degree\n");
	printf("17: Test all functions\n");
	printf("18: Exit\n");
}