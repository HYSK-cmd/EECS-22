#include "DIPs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Black and White */
Image *BlackNWhite(Image *image){
    assert(image != NULL && "Error: invalid input image.\n");
    int WIDTH = image->W, HEIGHT = image->H;
    Image *bw_Img = NULL;
    bw_Img = CreateImage(WIDTH, HEIGHT); //Allocate dynamic memory for image_bw

    int avg;

    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            // Change the intensity value of each color; Red, Green, and Blue
            avg = (GetPixelR(image, i, j) + GetPixelG(image, i, j) + GetPixelB(image, i, j)) / 3;
            SetPixelR(bw_Img, i, j, avg);
            SetPixelG(bw_Img, i, j, avg);
            SetPixelB(bw_Img, i, j, avg);
        }
    }
    // Free the image
    DeleteImage(image);
    image = NULL;
    return bw_Img;
}
/* Reverse image color */
Image *Negative(Image *image){
    assert(image != NULL && "Error: invalid input image.\n");
    int WIDTH = image->W, HEIGHT = image->H;
    Image *negative_Img = NULL;
    negative_Img = CreateImage(WIDTH, HEIGHT); //Allocate dynamic memory for negative_Img

    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            // Subtract from MAX_PIXEL, 255
            unsigned char r = MAX_PIXEL - GetPixelR(image, i, j);
            unsigned char g = MAX_PIXEL - GetPixelG(image, i, j);
            unsigned char b = MAX_PIXEL - GetPixelB(image, i, j);
            SetPixelR(negative_Img, i, j, r);
            SetPixelG(negative_Img, i, j, g);
            SetPixelB(negative_Img, i, j, b);
        }
    }
    DeleteImage(image);
    image = NULL;
    return negative_Img;
}

/* Color filter */
Image *ColorFilter(Image *image, int target_r, int target_g, int target_b, 
                    int threshold, int replace_r, int replace_g, int replace_b){
    assert(image != NULL && "Error: invalid input image.\n");
    int WIDTH = image->W, HEIGHT = image->H;
    Image *colorFilter_Img = NULL;
    colorFilter_Img = CreateImage(WIDTH, HEIGHT); //Allocate dynamic memory for colorFilter_Img

    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            // Set a boundary
            if((GetPixelR(image, i, j) >= target_r - threshold && GetPixelR(image, i, j) <= target_r + threshold)
            && (GetPixelG(image, i, j) >= target_g - threshold && GetPixelG(image, i, j) <= target_g + threshold)
            && (GetPixelB(image, i, j) >= target_b - threshold && GetPixelB(image, i, j) <= target_b + threshold)){
                SetPixelR(colorFilter_Img, i, j, replace_r);
                SetPixelG(colorFilter_Img, i, j, replace_g);
                SetPixelB(colorFilter_Img, i, j, replace_b);
            } else {
                // If out of range, keep the current color
                SetPixelR(colorFilter_Img, i, j, GetPixelR(image, i, j));
                SetPixelG(colorFilter_Img, i, j, GetPixelG(image, i, j));
                SetPixelB(colorFilter_Img, i, j, GetPixelB(image, i, j));
            }
        }
    }
    DeleteImage(image);
    image = NULL;
    return colorFilter_Img;
}

/* Edge detection */
Image *Edge(Image *image){
    assert(image != NULL && "Error: invalid input image.\n");
    int WIDTH = image->W, HEIGHT = image->H;
    Image *edge_Img = NULL;
    edge_Img = CreateImage(WIDTH, HEIGHT); //Allocate dynamic memory for edge_Img

    int red, green, blue;

    // Calculate every pixel except for image boundaries
    for(int i = 1; i < WIDTH - 1; i++){
        for(int j = 1; j < HEIGHT - 1; j++){
            // Variable used to detect the edge
            red = (- GetPixelR(image, i-1, j-1) - GetPixelR(image, i-1, j) - GetPixelR(image, i-1, j+1)
                   - GetPixelR(image, i,   j-1) + (8*GetPixelR(image, i, j)) - GetPixelR(image, i  , j+1)
                   - GetPixelR(image, i+1, j-1) - GetPixelR(image, i+1, j) - GetPixelR(image, i+1, j+1));
            green = (- GetPixelG(image, i-1, j-1) - GetPixelG(image, i-1, j) - GetPixelG(image, i-1, j+1)
                   - GetPixelG(image, i,   j-1) + (8*GetPixelG(image, i, j)) - GetPixelG(image, i  , j+1)
                   - GetPixelG(image, i+1, j-1) - GetPixelG(image, i+1, j) - GetPixelG(image, i+1, j+1));
            blue = (- GetPixelB(image, i-1, j-1) - GetPixelB(image, i-1, j) - GetPixelB(image, i-1, j+1)
                   - GetPixelB(image, i,   j-1) + (8*GetPixelB(image, i, j)) - GetPixelB(image, i  , j+1)
                   - GetPixelB(image, i+1, j-1) - GetPixelB(image, i+1, j) - GetPixelB(image, i+1, j+1));
            // Use a saturated arithmetic; keep the value in range between 0 and 255
            if(red < 0){
                SetPixelR(edge_Img, i, j, 0);
            } else if(red > MAX_PIXEL){
                SetPixelR(edge_Img, i, j, MAX_PIXEL);
            } else {
                SetPixelR(edge_Img, i, j, red);
            } 
            if(green < 0){
                SetPixelG(edge_Img, i, j, 0);
            } else if(green > MAX_PIXEL){
                SetPixelG(edge_Img, i, j, MAX_PIXEL);
            } else {
                SetPixelG(edge_Img, i, j, green);
            }
            if(blue < 0){
                SetPixelB(edge_Img, i, j, 0);
            } else if(blue > MAX_PIXEL){
                SetPixelB(edge_Img, i, j, MAX_PIXEL);
            } else {
                SetPixelB(edge_Img, i, j, blue);
            }
        } 
    }
    //Make a black boundary
    for (int i = 0; i < WIDTH; i++) {
        SetPixelR(edge_Img, i, 0, 0);
        SetPixelG(edge_Img, i, 0, 0);
        SetPixelB(edge_Img, i, 0, 0);
        SetPixelR(edge_Img, i, HEIGHT - 1, 0);
        SetPixelG(edge_Img, i, HEIGHT - 1, 0);
        SetPixelB(edge_Img, i, HEIGHT - 1, 0);
    }
    for (int i = 0; i < HEIGHT; i++) {
        SetPixelR(edge_Img, 0, i, 0);
        SetPixelG(edge_Img, 0, i, 0);
        SetPixelB(edge_Img, 0, i, 0);
        SetPixelR(edge_Img, WIDTH - 1, i, 0);
        SetPixelG(edge_Img, WIDTH - 1, i, 0);
        SetPixelB(edge_Img, WIDTH - 1, i, 0);
    }

    DeleteImage(image);
    image = NULL;
    return edge_Img;
}

/* Shuffle an image */
Image *Shuffle(Image *image){
    assert(image != NULL && "Error: invalid input image.\n");
    int WIDTH = image->W, HEIGHT = image->H;
    Image *shuffle_Img = NULL;
    shuffle_Img = CreateImage(WIDTH, HEIGHT); //Allocate dynamic memory for shuffle_Img

    int block_WIDTH = WIDTH / SHUFF_WIDTH_DIV;
    int block_HEIGHT = HEIGHT / SHUFF_HEIGHT_DIV;
    int pairs[8][2] = {{1, 16}, {2, 15}, {3, 14}, {4, 13}, 
                       {5, 12}, {6, 11}, {7, 10}, {8, 9}};
    // Coordinate of Each Element in pairs 2D array
    // {1=(0,0), 16=(1,0)}, {2=(2,0), 15=(3,0)}, {2=(4,0), 15=(5,0)}, {2=(6,0), 15=(7,0)}
    // {2=(0,0), 15=(1,1)}, {2=(2,1), 15=(3,1)}, {2=(4,1), 15=(5,1)}, {2=(6,1), 15=(7,1)}

    for(int n = 0; n < 8; n++){
        int B1 = pairs[n][0] - 1;
        int B2 = pairs[n][1] - 1; 
        // WIDTH_STARTING_PTS  = (0 or 128 or 256 or 384)
        // HEIGHT_STARTING_PTS = (0 or 72 or 144 or 216)
        unsigned int  x1_pt = (B1 % 4) * block_WIDTH;
        unsigned int  y1_pt = (B1 / 4) * block_HEIGHT;
        unsigned int  x2_pt = (B2 % 4) * block_WIDTH;
        unsigned int  y2_pt = (B2 / 4) * block_HEIGHT;
        for(int i = 0; i < block_WIDTH; i++){
            for(int j = 0; j < block_HEIGHT; j++){
                // Set vertical&horizontal starting point
                unsigned int x1 = i + x1_pt;
                unsigned int y1 = j + y1_pt;
                unsigned int x2 = i + x2_pt;
                unsigned int y2 = j + y2_pt;
                // Swap the pairs
                // Swap R value
                unsigned char temp1 = GetPixelR(image, x1, y1);
                SetPixelR(shuffle_Img, x1, y1, GetPixelR(image, x2, y2));
                SetPixelR(shuffle_Img, x2, y2, temp1);
                // Swap G value
                unsigned char temp2 = GetPixelG(image, x1, y1);
                SetPixelG(shuffle_Img, x1, y1, GetPixelG(image, x2, y2));
                SetPixelG(shuffle_Img, x2, y2, temp2);
                // Swap B value
                unsigned char temp3 = GetPixelB(image, x1, y1);
                SetPixelB(shuffle_Img, x1, y1, GetPixelB(image, x2, y2));
                SetPixelB(shuffle_Img, x2, y2, temp3);
            }
        }
    }
    DeleteImage(image);
    image = NULL;
    return shuffle_Img;
}

/* Flip image vertically */
Image *VFlip(Image *image){
    assert(image != NULL && "Error: invalid input image.\n");
    int WIDTH = image->W, HEIGHT = image->H;
    Image *vflip_Img = NULL;
    vflip_Img = CreateImage(WIDTH, HEIGHT); //Allocate dynamic memory for vflip_Img

    // Pairs to swap: (0,0) & (0,287), (0,1) & (0,286), and so on
    // Swap only vertical index j
    for(int j = 0; j < HEIGHT / 2; j++){
        for(int i = 0; i < WIDTH; i++){
            // Swap R value
            unsigned char temp1 = GetPixelR(image, i, j);
            SetPixelR(vflip_Img, i, j, GetPixelR(image, i, HEIGHT - 1 - j));
            SetPixelR(vflip_Img, i, HEIGHT - 1 - j, temp1);
            // Swap G value
            unsigned char temp2 = GetPixelG(image, i, j);
            SetPixelG(vflip_Img, i, j, GetPixelG(image, i, HEIGHT - 1 - j));
            SetPixelG(vflip_Img, i, HEIGHT - 1 - j, temp2);
            // Swap B value
            unsigned char temp3 = GetPixelB(image, i, j);
            SetPixelB(vflip_Img, i, j, GetPixelB(image, i, HEIGHT - 1 - j));
            SetPixelB(vflip_Img, i, HEIGHT - 1 - j, temp3);
        }
    }
    DeleteImage(image);
    image = NULL;
    return vflip_Img;
}

/* Mirror image vertically */
Image *HMirror(Image *image){
    assert(image != NULL && "Error: invalid input image.\n");
    int WIDTH = image->W, HEIGHT = image->H;
    Image *hmirror_Img = NULL;
    hmirror_Img = CreateImage(WIDTH, HEIGHT); //Allocate dynamic memory for hmirror_Img
    for(int i = 0; i < WIDTH / 2; i++){
        for(int j = 0; j < HEIGHT; j++){
            SetPixelR(hmirror_Img, WIDTH - 1 - i, j, GetPixelR(image, i, j));
            SetPixelG(hmirror_Img, WIDTH - 1 - i, j, GetPixelG(image, i, j));
            SetPixelB(hmirror_Img, WIDTH - 1 - i, j, GetPixelB(image, i, j));
        }
    }
    for(int i = 0; i < WIDTH / 2; i++){
        for(int j = 0; j < HEIGHT; j++){
            SetPixelR(hmirror_Img, i, j, GetPixelR(image, i, j));
            SetPixelG(hmirror_Img, i, j, GetPixelG(image, i, j));
            SetPixelB(hmirror_Img, i, j, GetPixelB(image, i, j));
        }
    }
    // Free the image
    DeleteImage(image);
    image = NULL;
    return hmirror_Img;
}

/* Pixelate an image */
Image *Pixelate(Image *image, int block_size){
    assert(image != NULL && "Error: invalid input image.\n");
    int WIDTH = image->W, HEIGHT = image->H;
    Image *pixelate_Img = NULL;
    pixelate_Img = CreateImage(WIDTH, HEIGHT);

    for(int i = 0; i < WIDTH; i+=block_size){
        for(int j = 0; j < HEIGHT; j+=block_size){
            int R_sum = 0, G_sum = 0, B_sum = 0;
            int count = 0;
            //Calculate the average RGB value in each block
            for(int x = i; x < i + block_size && x < WIDTH; x++){
                for(int y = j; y < j + block_size && y < HEIGHT; y++){
                    R_sum += GetPixelR(image, x, y);
                    G_sum += GetPixelG(image, x, y);
                    B_sum += GetPixelB(image, x, y);
                    count++;
                }
            }
            unsigned char R_avg = R_sum / count;
            unsigned char G_avg = G_sum / count;
            unsigned char B_avg = B_sum / count;

            for(int x = i; x < i + block_size && x < WIDTH; x++){
                for(int y = j; y < j + block_size && y < HEIGHT; y++){
                    SetPixelR(pixelate_Img, x, y, R_avg);
                    SetPixelG(pixelate_Img, x, y, G_avg);
                    SetPixelB(pixelate_Img, x, y, B_avg);
                }
            }
        }
    }
    // Free the image
    DeleteImage(image);
    image = NULL;
    return pixelate_Img;
}

/* Add a border to an image */
Image *AddBorder(Image *image, char *color, int border_width){
    // Allocate dynamic memory for border_Img
    assert(image != NULL && "Error: invalid input image.\n");
    int WIDTH = image->W, HEIGHT = image->H;
    Image *border_Img = NULL;
    border_Img = CreateImage(WIDTH, HEIGHT);

    // Default border color
	int border_r = MAX_PIXEL;
	int border_g = MAX_PIXEL;
	int border_b = MAX_PIXEL;

    // Assign RGB values based on the selected border color
	if (!strcmp(color, "black")) {
		border_r = 0;
		border_g = 0;
		border_b = 0;
	} else if (!strcmp(color, "white")) {
		border_r = MAX_PIXEL;
		border_g = MAX_PIXEL;
		border_b = MAX_PIXEL;
	} else if (!strcmp(color, "red")) {
		border_r = MAX_PIXEL;
		border_g = 0;
		border_b = 0;
	} else if (!strcmp(color, "green")) {
		border_r = 0;
		border_g = MAX_PIXEL;
		border_b = 0;
	} else if (!strcmp(color, "blue")) {
		border_r = 0;
		border_g = 0;
		border_b = MAX_PIXEL;
	} else if (!strcmp(color, "yellow")) {
		border_r = MAX_PIXEL;
		border_g = MAX_PIXEL;
		border_b = 0;
	} else if (!strcmp(color, "cyan")) {
		border_r = 0;
		border_g = MAX_PIXEL;
		border_b = MAX_PIXEL;
	} else if (!strcmp(color, "pink")) {
		border_r = MAX_PIXEL;
		border_g = 192;
		border_b = 203;
	} else if (!strcmp(color, "orange")) {
		border_r = MAX_PIXEL;
		border_g = 165;
		border_b = 0;
	} else {
		printf("Unsupported color.\n");
		return image;
	}
    // Iterate through every pixel
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
            // Apply border color to pixels within the border area
			if ((y < border_width) || (y > HEIGHT - 1 - border_width) || 
            (x < border_width) || (x > WIDTH - 1 - border_width)) {
                SetPixelR(border_Img, x, y, border_r);
                SetPixelG(border_Img, x, y, border_g);
                SetPixelB(border_Img, x, y, border_b);
			} else {
                // Copy original pixel values for the inner image
                SetPixelR(border_Img, x, y, GetPixelR(image, x, y));
                SetPixelG(border_Img, x, y, GetPixelG(image, x, y));
                SetPixelB(border_Img, x, y, GetPixelB(image, x, y));
            }
		}
	}
    // Free the memory
    DeleteImage(image);
    image = NULL;
    return border_Img;
}

/* Shift */
Image *Shift(Image *image, int shiftX, int shiftY){
    // Allocate dynamic memory for shift_Img
    assert(image != NULL && "Error: invalid input image.\n");
    int WIDTH = image->W, HEIGHT = image->H;
    Image *shift_Img = NULL;
    shift_Img = CreateImage(WIDTH, HEIGHT);
    
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            // Any pixel values off the screen will be rolled over onto the opposite end
            int x = (i + shiftX) % WIDTH;
            int y = (j + shiftY) % HEIGHT;
            // Set RGB values to the shifted_Img
            SetPixelR(shift_Img, x, y, GetPixelR(image, i, j));
            SetPixelG(shift_Img, x, y, GetPixelG(image, i, j));
            SetPixelB(shift_Img, x, y, GetPixelB(image, i, j));
        }
    }
    // Free the image
    DeleteImage(image);
    image = NULL;
    return shift_Img;
}