/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2025                   */
/* MovieLab.c: source file for the main function                     */
/* Please use this template for your HW5.                            */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"

/* Load one movie frame from the input file */
YUVImage* LoadOneFrame(const char* fname, int n,
	unsigned int width, unsigned height);

/* Load the movie frames from the input file */
Movie *LoadMovie(const char *fname, int frameNum,
	unsigned int width, unsigned height);

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVImage *image, const char *fname, FILE *file);

/* Save the movie frames to the output file */
int SaveMovie(const char *fname, Movie *movie);

/* Print the command-line arguments usage of the program */
void PrintUsage();

int main(int argc, char *argv[]) {
	int x = 0;
	char *fin = NULL;
	char *fout = NULL;
	
	unsigned int width = 512;
	unsigned int height = 288;
	Movie *movie_ld = NULL;

	unsigned int frame_num = 0;
	int s_exist = 0;
	/* the while loop to check options in the command line */
	while (x < argc) {
		/* the input file name */
		if (strcmp(argv[x], "-i") == 0) {
			if (x < argc - 1) {
				fin = argv[x + 1];
			}
			else {
				printf("Missing argument for the input file name!\n");
				return 5;
			}
			x += 2;
			continue;
		}

		/* the output file name */
		if (strcmp(argv[x], "-o") == 0) {
			if (x < argc - 1) {
				fout = argv[x + 1];
			}
			else {
				printf("Missing argument for the output file name!\n");
				return 5;
			}
			x += 2;
			continue;
		}

		/* the help option */
		if (strcmp(argv[x], "-h") == 0) {
			PrintUsage();
			return 0;
		}
		
		/* resolution of input stream */
		if (strcmp(argv[x], "-s") == 0) {
			if (x < argc - 1){
				if (sscanf(argv[x+1], "%ux%u", &width, &height) == 2) {
					s_exist = 1;
				} else {
					printf("Error: Invalid format. Use -s WidthxHeight.\n");
					return 5;
				}
			} else {
				printf("Missing argument for resolution!\n");
				return 5;
			}
			x += 2;
			continue;
		}

		/* frame numbers */
		if (strcmp(argv[x], "-f") == 0) {
			if (x < argc - 1) {
				if (sscanf(argv[x+1], "%u", &frame_num) == 1){
				} else {
					printf("Invalid command!\n");
					return 5;
				}
			} else {
				printf("Missing argument for frame numbers!\n");
				return 5;
			}
			x += 2;
			continue;
		}
		/* black&white movie */
		if (strcmp(argv[x], "-bw") == 0) {
			if(movie_ld == NULL){
				movie_ld = LoadMovie(fin, frame_num, width, height);
			}
			YUV2RGBMovie(movie_ld);
			IENTRY *firstEntry = movie_ld->Frames->First;
			while(firstEntry){
				BlackNWhite((Image *)(firstEntry->image));
				firstEntry = firstEntry->Next;
			}
			RGB2YUVMovie(movie_ld);
			printf("Operation Black and White is done!\n");
			x++;
			continue;
		}
		if (strcmp(argv[x], "-hmirror") == 0) {
			if(movie_ld == NULL){
				movie_ld = LoadMovie(fin, frame_num, width, height);
			}
			YUV2RGBMovie(movie_ld);
			IENTRY *firstEntry = movie_ld->Frames->First;
			while(firstEntry){
				HMirror((Image *)(firstEntry->image));
				firstEntry = firstEntry->Next;
			}
			RGB2YUVMovie(movie_ld);
			printf("Operation HMirror is done!\n");
			x++;
			continue;
		}
		if (strcmp(argv[x], "-edge") == 0) {
			if(movie_ld == NULL){
				movie_ld = LoadMovie(fin, frame_num, width, height);
			}
			YUV2RGBMovie(movie_ld);
			IENTRY *firstEntry = movie_ld->Frames->First;
			while(firstEntry){
				Edge((Image *)(firstEntry->image));
				firstEntry = firstEntry->Next;
			}
			RGB2YUVMovie(movie_ld);
			printf("Operation Edge is done!\n");
			x++;
			continue;
		}
		if (strcmp(argv[x], "-crop") == 0) {
			if (x < argc - 1){
				unsigned int start = 0, end = 0;
				if (sscanf(argv[x+1], "%u-%u", &start, &end) == 2){
					if (movie_ld == NULL) {
						movie_ld = LoadMovie(fin, frame_num, width, height);
					}
					YUV2RGBMovie(movie_ld);
					CropImageList(movie_ld->Frames, start, end);
					RGB2YUVMovie(movie_ld);
					printf("Operation Crop is done! New number of frames is %u.\n", end - start + 1);
				} else {
					printf("Missing argument for start and end!\n");
					return 5;
				}
			}
			x += 2;
			continue;
		}
		if (strcmp(argv[x], "-fast") == 0) {
			if (x < argc - 1){
				unsigned int factor = 0;
				if (sscanf(argv[x+1], "%u", &factor) == 1){
					if (movie_ld == NULL) {
						movie_ld = LoadMovie(fin, frame_num, width, height);
					}
					YUV2RGBMovie(movie_ld);
					FastImageList(movie_ld->Frames, factor);
					RGB2YUVMovie(movie_ld);
					printf("Operation Fast Forward is done! New number of frames is %u.\n", factor);
				} else {
					printf("Missing argument for factor!\n");
					return 5;
				}
			}
			x += 2;
			continue;
		}
		if (strcmp(argv[x], "-reverse") == 0) {
			if (movie_ld == NULL) {
				movie_ld = LoadMovie(fin, frame_num, width, height);
			}
			if (movie_ld->Frames->First == NULL) {
				printf("Error: Cannot reverse an empty movie list.\n");
				return 5;
			}
			YUV2RGBMovie(movie_ld);
			ReverseImageList(movie_ld->Frames);
			RGB2YUVMovie(movie_ld);
			printf("Operation Reverse is done!\n");
			x++;
			continue;
		}
		if (strcmp(argv[x], "-watermark") == 0) {
			if (x < argc - 1){
				char *watermarkppm = argv[x+1];
				srand(time(NULL)); // seed random number generator
				if (movie_ld == NULL) {
					movie_ld = LoadMovie(fin, frame_num, width, height);
				}
				Image *watermark = LoadImage(watermarkppm);
				YUV2RGBMovie(movie_ld);
				IENTRY *ENTRY = movie_ld->Frames->First;
				int frame_n = 0;
				unsigned int imgW = width;
				unsigned int imgH = height;
				unsigned int watermark_W = watermark->W;
				unsigned int watermark_H = watermark->H;
				// generate random starting coordinates
				unsigned int topLeftX = rand() % (imgW - watermark_W + 1);
				unsigned int topLeftY = rand() % (imgH - watermark_H + 1);
				while(ENTRY){
					//every 15 frames
					if (frame_n % 15 == 0){
						topLeftX = rand() % (imgW - watermark_W + 1);
                		topLeftY = rand() % (imgH - watermark_H + 1);
					}
					Watermark((Image *)(ENTRY->image), watermark, topLeftX, topLeftY);
        			ENTRY = ENTRY->Next;
					frame_n++;
				}
        		RGB2YUVMovie(movie_ld);
        		DeleteImage(watermark);
				printf("Operation Watermark is done!\n");
			}
			x += 2;
			continue;
		}
		if (strcmp(argv[x], "-spotlight") == 0) {
			if (movie_ld == NULL) {
				movie_ld = LoadMovie(fin, frame_num, width, height);
			}
			if (frame_num < 40) {
				printf("Error: at least 40 frames required\n");
				return 5;
			}
			IENTRY *ENTRY = movie_ld->Frames->First;
			int centerX = width/2, centerY = height/2;
			int frame_n = 0;
			unsigned int max_radius = sqrt((width/2 * width/2) + (height/2 * height/2));
			unsigned int radius = 0;
			YUV2RGBMovie(movie_ld);
			//for the first 20 frames, spotlight effect fades in
			Image *first20Frame = CopyRGBImage((Image *)(ENTRY->image));
			for(int i = 19; i >= 0; i--){
				radius = (max_radius * i) / 20;
				Image *new20Frame = CopyRGBImage(first20Frame);
				Spotlight(new20Frame, centerX, centerY, radius);
				PrependRGBImage(movie_ld->Frames, new20Frame); //since we put it at the beginning
				frame_n++;
			}
			DeleteImage(first20Frame);
			//start the first entry: moving part
			ENTRY = movie_ld->Frames->First;
			//The image starts moving
			while(ENTRY && frame_n < frame_num + 20)
			{
				ENTRY = ENTRY->Next;
				frame_n++;
			}
			//ends the last entry
			ENTRY = movie_ld->Frames->Last;
			//for the last 20 frames, spotlight effect fades out
			Image *last20Frame = CopyRGBImage((Image *)(ENTRY->image));
			for(int i = 0; i < 20; i++){
				radius = (max_radius * (20 - i)) / 20;
				Image *new20Frame = CopyRGBImage(last20Frame);
				Spotlight(new20Frame, centerX, centerY, radius);
				AppendRGBImage(movie_ld->Frames, new20Frame); //since we put it at the end
				frame_n++;
			}
			DeleteImage(last20Frame);

			RGB2YUVMovie(movie_ld);
			printf("Operation Spotlight is done!\n");
			x++;
			continue;
		}
		if (strcmp(argv[x], "-rotate") == 0){
			if (movie_ld == NULL) {
				movie_ld = LoadMovie(fin, frame_num, width, height);
			}
			IENTRY *ENTRY = movie_ld->Frames->First;
			int frame_n = 0;
			YUV2RGBMovie(movie_ld);
			//for the first 20 frames, rotate effect comes in
			Image *first20Frame = CopyRGBImage((Image *)(ENTRY->image));
			for(int i = 20; i > 0; i--){
				double Angle = i - 20.0; // 20 degree to 0 degree; CW
				double Scalefactor = 0.2 + (i * 0.04); // ZOOM IN
				Image *new20Frame = Rotate(first20Frame, Angle, Scalefactor);
				PrependRGBImage(movie_ld->Frames, new20Frame); //since we put it at the beginning
				frame_n++;
			}
			DeleteImage(first20Frame);
			//The image starts moving
			while (ENTRY && frame_n < frame_num + 20) {
				ENTRY = ENTRY->Next;
				frame_n++;
			}
			//ends the last entry
			ENTRY = movie_ld->Frames->Last;
			//for the last 20 frames, rotate effect comes in
			Image *last20Frame = CopyRGBImage((Image *)(ENTRY->image));
			for(int i = 0; i < 20; i++){
				double Angle = -i; // 0 degree to 20 degree; CCW
				double Scalefactor = 1.0 - (i * 0.04); // ZOOM OUT
				Image *new20Frame = Rotate(last20Frame, Angle, Scalefactor);
				AppendRGBImage(movie_ld->Frames, new20Frame); //since we put it at the end
				frame_n++;
			}
			DeleteImage(last20Frame);

			RGB2YUVMovie(movie_ld);
			printf("Operation Spotlight is done!\n");
			x++;
			continue;
		}
		x++;
	}
	if (fin == NULL) {
		printf("Missing argument for the input file name!\n");
		PrintUsage();
		return 5;
	}

	if (fout == NULL) {
		printf("Missing argument for the output file name!\n");
		PrintUsage();
		return 5;
	}
	// Extract dimensions from filename if -s is not provided
    if (!s_exist) {
        char *first_ = strchr(fin, '_'); 		// Find the first underscore
		char *last_  = strchr(first_ + 1, '_'); // Find the last underscore
		char *dot 	 = strchr(first_ + 1, '.'); // Find the dot
		if (first_ && last_ && dot){
			sscanf(first_ + 1, "%u", &width);
        	sscanf(last_ + 1, "%u", &height);
		} else {
			printf("neither the “-s” option nor the filename is given\n");
			perror("Out of Memory. Aborting..");
			exit(10);
		}
    }
	//save and delete movie
	SaveMovie(fout, movie_ld);
	DeleteMovie(movie_ld);	

	fin = NULL;
	fout = NULL;

	return 0;
}

void PrintUsage()
{
	printf("\nUsage: MovieLab -i <file> -o <file> -f <framenum> [options]\n"
	       "Options:\n"
	       "-s <WidthxHeight>     To set the resolution of the input stream (WidthxHeight)\n"
	       "-bw                   Activate the black and white filter on every movie frame\n"
	       "-hmirror              Activate horizontal mirror on every movie frame\n"
	       "-edge                 Activate the edge filter on every movie frame\n"
	       "-crop <start-end>     Crop the movie frames from <start> to <end>\n"
	       "-fast <factor>        Fast forward the movie by <factor>\n"
	       "-reverse              Reverse the frame order of the input movie\n"
	       "-watermark <file>     Add a watermark from <file> to every movie frame\n"
	       "-spotlight            Spotlight the fade in and fade out\n"
	       "-rotate               Rotate and zoom in/out the input movie\n"
	       "-h                    Display this usage information\n"
	      );
}

/* Load one movie frame from the input file */
YUVImage* LoadOneFrame(const char* fname, int n,
	unsigned int width, unsigned height)
{
	FILE *file;
	unsigned int x, y;
	unsigned char c;
	YUVImage* YUVimage;

	/* Check errors */
	assert(fname);
	assert(n >= 0);

	YUVimage = CreateYUVImage(width, height);
	if (YUVimage == NULL) {
		return NULL;
	}

	/* Open the input file */
	file = fopen(fname, "r");
	if (file == NULL) {
		DeleteYUVImage(YUVimage);
		return NULL;
	}

	/* Find the desired frame */
	fseek(file, 1.5 * n * width * height, SEEK_SET);

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			c = fgetc(file);
			SetPixelY(YUVimage, x, y, c);
		} /*rof*/
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelU(YUVimage, x, y, c);
			SetPixelU(YUVimage, x + 1, y, c);
			SetPixelU(YUVimage, x, y + 1, c);
			SetPixelU(YUVimage, x + 1, y + 1, c);
		}
	}

	for (y = 0; y < height; y += 2) {
		for (x = 0; x < width; x += 2) {
			c = fgetc(file);
			SetPixelV(YUVimage, x, y, c);
			SetPixelV(YUVimage, x + 1, y, c);
			SetPixelV(YUVimage, x, y + 1, c);
			SetPixelV(YUVimage, x + 1, y + 1, c);
		}
	}

	/* Check errors */
	assert(ferror(file) == 0);

	/* Close the input file and return */
	fclose(file);
	file = NULL;
	return YUVimage;
}

/* Load the movie frames from the input file */
Movie *LoadMovie(const char *fname, int frameNum, 
	unsigned int width, unsigned int height)
{
    /* Allocate movie structure */
    Movie *movie = CreateMovie();
    assert(movie);

    /* Load frames one by one */
    for (int i = 0; i < frameNum; i++) {
        YUVImage *frame = LoadOneFrame(fname, i, width, height);
        AppendYUVImage(movie->Frames, frame);
    }
	printf("The movie file %s has been read successfully!\n", fname);
    return movie;
}


/* Save the movie frames to the output file */
int SaveMovie(const char *fname, Movie *movie)
{
	int count;
	FILE *file;
	IENTRY *curr;

	/* Open the output file */
	file = fopen(fname, "w");
	if (file == NULL) {
		return 1;
	}

	count = 0;
	curr = movie->Frames->First;
	while (curr != NULL) {

		SaveOneFrame(curr->image, fname, file);
		curr = curr->Next;
		count++;
	}

	fclose(file);
	file = NULL;

	printf("The movie file %s has been written successfully!\n", fname);
	printf("%d frames are written to the file %s in total.\n", count, fname);
	return 0;
}

/* Saves one movie frame to the output file */
void SaveOneFrame(YUVImage *image, const char *fname, FILE *file)
{
	int x, y;
	for (y = 0; y < image->H; y++) {
		for (x = 0; x < image->W; x++) {
			fputc(GetPixelY(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelU(image, x, y), file);
		}
	}

	for (y = 0; y < image->H; y += 2) {
		for (x = 0; x < image->W; x += 2) {
			fputc(GetPixelV(image, x, y), file);
		}
	}
}
/* EOF */
