/*****************************************************/
/* Advanced.c: program file for new filters          */
/*****************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Advanced.h"

/* Create a fisheye image W24 */
void FishEye(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
             double distortion_factor, double scaling_factor, double k){
    unsigned char   R_out[WIDTH][HEIGHT];
    unsigned char   G_out[WIDTH][HEIGHT];
    unsigned char   B_out[WIDTH][HEIGHT];

    double center_x = WIDTH / 2.0;
    double center_y = HEIGHT / 2.0;

    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            // Calculate the normalized distance from the center
            double dx = (x - center_x) / center_x;
            double dy = (y - center_y) / center_y;
            double rad = sqrt(pow(dx, 2) + pow(dy, 2));
            // Calculate the distortion factor based on radius
            double dist = 1.0 + (k * (rad * rad));
            // Apply fisheye transformation (polar coordinates)
            double theta = atan2(dy, dx);
            double new_rad = (rad * distortion_factor) / (dist * scaling_factor);
            // Convert back to Cartesian coordinates
            int x_src = (int)(center_x + (new_rad * cos(theta) * center_x));
            int y_src = (int)(center_y + (new_rad * sin(theta) * center_y));
            // Check if source coordinates are within bounds and copy pixel
            if((x_src >= 0 && x_src <= WIDTH) && (y_src >= 0 && y_src <= HEIGHT)){
                R_out[x][y] = R[x_src][y_src];
                G_out[x][y] = G[x_src][y_src];
                B_out[x][y] = B[x_src][y_src];
            } else {
                R_out[x][y] = 0;
                G_out[x][y] = 0;
                B_out[x][y] = 0;
            }
        }
    }
    // Copy the result back to the original image arrays
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            R[x][y] = R_out[x][y];
            G[x][y] = G_out[x][y];
            B[x][y] = B_out[x][y];
        }
    }
}

/* posterize the image */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
               unsigned int rbits, unsigned int gbits, unsigned int bbits) {
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            //clear = complement of 2^n-1
            unsigned char r_clear = ~(1 << (rbits - 1)); //clear = complement of 2^n-1
            unsigned char r_mask = (1 << (rbits - 1)) - 1; //bit_mask to set nth bit 0
            R[x][y] = (R[x][y] & r_clear) | r_mask; //set nth bit 0; set lower bits 1; keep higher bits unchanged

            unsigned char g_clear = ~(1 << (gbits - 1));
            unsigned char g_mask = (1 << (gbits - 1)) - 1;
            G[x][y] = (G[x][y] & g_clear) | g_mask;

            unsigned char b_clear = ~(1 << (bbits - 1));
            unsigned char b_mask = (1 << (bbits - 1)) - 1;
            B[x][y] = (B[x][y] & b_clear) | b_mask;
        }
    }
}

/* rotate and zoom the image */
void Rotate(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
            double Angle, double ScaleFactor, int CenterX, int CenterY){
    unsigned char   R_new[WIDTH][HEIGHT];
    unsigned char   G_new[WIDTH][HEIGHT];
    unsigned char   B_new[WIDTH][HEIGHT];

    const double PI = 3.141592653589793;
    // Convert the angle to radian
    double rad = Angle * (PI / 180);
    // Rotate counter-clockwise 
    /* Matrix 2x2 
        [ cos() sin()]
        [-sin() cos()]
                        */
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            // Simplify the calculation of dx and dy
            int dx = (int)((((cos(rad) / ScaleFactor) * (x - CenterX)) + ((sin(rad) / ScaleFactor) * (y - CenterY))) + CenterX);
            int dy = (int)((((-sin(rad) / ScaleFactor) * (x - CenterX)) + ((cos(rad) / ScaleFactor) * (y - CenterY))) + CenterY);
            // Check if dx and dt are within bounds and copy pixel; otherwise fill in black
            if((dx >= 0 && dx < WIDTH) && (dy >= 0 && dy < HEIGHT)){
                R_new[x][y] = R[dx][dy];
                G_new[x][y] = G[dx][dy];
                B_new[x][y] = B[dx][dy];
            } else {
                R_new[x][y] = 0;
                G_new[x][y] = 0;
                B_new[x][y] = 0;
            }
        }
    }
    // Copy the result back to the original image arrays
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            R[x][y] = R_new[x][y];
            G[x][y] = G_new[x][y];
            B[x][y] = B_new[x][y];
        }
    }
}
/* motion blur */
void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            int r_sum = 0;
            int g_sum = 0;
            int b_sum = 0;
            int n = 0; // Count for equal weight distribution
            // Sum up the valid neighboring pixels within BlurAmount
            for (int z = 1; z <= BlurAmount; z++) {
                if (x + z < WIDTH) {
                    r_sum += R[x + z][y];
                    g_sum += G[x + z][y];
                    b_sum += B[x + z][y];
                    n++;
                }
            }
            // In case no valid pixels were added
            if (n > 0) {
                // (original_channel_value + (summation_of_channel) / n) / 2
                R[x][y] = (unsigned char)((R[x][y] + (r_sum / n)) / 2);
                G[x][y] = (unsigned char)((G[x][y] + (g_sum / n)) / 2);
                B[x][y] = (unsigned char)((B[x][y] + (b_sum / n)) / 2);
            }
        }
    }
}