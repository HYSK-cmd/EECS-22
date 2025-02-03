/*********************************************************************/
/* PhotoLab.c: Assignment 2 for EECS 22, Winter 2024                 */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*** global definitions ***/
#define WIDTH  512              /* image width */
#define HEIGHT 288              /* image height */
#define SLEN    80              /* maximum length of file names */

/*** function declarations ***/

/* print a menu */
void PrintMenu(void);

/* read image from a file */
int LoadImage(const char fname[SLEN],
              unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
int SaveImage(const char fname[SLEN],
              unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/* change a color image to black & white */
void BlackNWhite(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT]);

/* reverse image color */
void Negative(unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

/* color filter */
void ColorFilter(unsigned char R[WIDTH][HEIGHT],
                 unsigned char G[WIDTH][HEIGHT],
                 unsigned char B[WIDTH][HEIGHT],
                 int target_r, int target_g, int target_b, int threshold,
                 int replace_r, int replace_g, int replace_b);

/* edge detection */
void Edge(unsigned char R[WIDTH][HEIGHT],
          unsigned char G[WIDTH][HEIGHT],
          unsigned char B[WIDTH][HEIGHT]);

/* mirror image horizontally */
void HMirror(unsigned char R[WIDTH][HEIGHT],
             unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* shuffle the image */
void Shuffle(unsigned char R[WIDTH][HEIGHT],
             unsigned char G[WIDTH][HEIGHT],
             unsigned char B[WIDTH][HEIGHT]);

/* add border */
void AddBorder(unsigned char R[WIDTH][HEIGHT],
               unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT],
               char color[SLEN], int border_width);

/* flip image vertically */
void VFlip(unsigned char R[WIDTH][HEIGHT],
           unsigned char G[WIDTH][HEIGHT],
           unsigned char B[WIDTH][HEIGHT]);


/* pixelate the image */
void Pixelate(unsigned char R[WIDTH][HEIGHT],
               unsigned char G[WIDTH][HEIGHT],
               unsigned char B[WIDTH][HEIGHT],
               int block_size);

/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT],
              unsigned char G[WIDTH][HEIGHT],
              unsigned char B[WIDTH][HEIGHT]);

int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];

    int option;
    int target_r, target_g, target_b;
    int threshold;
    int replace_r, replace_g, replace_b;
    int block_size;
    char filename[SLEN];
    /* Please replace the following code with proper menu with function calls for DIP operations */
    while(1){
        printf("--------------------------------\n");
        printf(" 1: Load a PPM image\n");
        printf(" 2: Save an image in PPM and JPEG format\n");
        printf(" 3: Change a color image to Black & White\n");
        printf(" 4: Make a negative of an image\n");
        printf(" 5: Color filter an image\n");
        printf(" 6: Sketch the edge of an image\n");
        printf(" 7: Shuffle an image\n");
        printf(" 8: Flip an image vertically\n");
        printf(" 9: Mirror an image horizontally\n");
        printf(" 10: Pixelate an image\n");
        printf(" 11: Test all functions\n");
        printf(" 12: Exit\n");
        printf(" please make your choice: ");
        scanf("%d", &option);
        switch (option){
            case 1:
                printf("Please input the file name to load: ");
                scanf("%s", filename);
                LoadImage(filename, R, G, B);
                break;
            case 2:
                printf("Please input the file name to save: ");
                scanf("%s", filename);
                SaveImage(filename, R, G, B);
                printf("");
                break;
            case 3:
                if(strlen(filename) == 0){
                    printf("Load an image first.\n");
                    break;
                }
                LoadImage(filename, R, G, B);
                BlackNWhite(R, G, B);
                SaveImage("bw", R, G ,B);
                printf("\"Black & White\" operation is done!\n");
            case 4:
                //if an image is not loaded, break the switch
                if(strlen(filename) == 0){ 
                    printf("Load an image first.\n");
                    break;
                }
                LoadImage(filename, R, G, B);
                Negative(R, G, B);
                SaveImage("negative", R, G, B);
                printf("\"Negative\" operation is done!\n");
                break;
            case 5:
                if(strlen(filename) == 0){
                    printf("Load an image first.\n");
                    break;
                }
                printf("Enter Red   component for the target color: ");
                scanf("%d", &target_r);
                printf("Enter Green component for the target color: ");
                scanf("%d", &target_g);
                printf("Enter Blue  component for the target color: ");
                scanf("%d", &target_b);
                printf("Enter threshold for the color difference: ");
                scanf("%d", &threshold);
                printf("Enter value for Red   component in the target color: ");
                scanf("%d", &replace_r);
                printf("Enter value for Green component in the target color: ");
                scanf("%d", &replace_g);
                printf("Enter value for Blue  component in the target color: ");
                scanf("%d", &replace_b);
                LoadImage(filename, R, G, B);
                ColorFilter(R, G, B, target_r, target_g, target_b, threshold, replace_r, replace_g, replace_b);
                SaveImage("colorfilter", R, G, B);
                printf("\"Color Filter\" operation is done!\n");
                break;
            case 6: 
                if(strlen(filename) == 0){
                    printf("Load an image first.\n");
                    break;
                }
                LoadImage(filename, R, G, B);
                Edge(R, G, B);
                SaveImage("edge", R, G, B);
                printf("\"Edge\" operation is done!\n");
                break;
            case 7:
                if(strlen(filename) == 0){
                    printf("Load an image first.\n");
                    break;
                }
                LoadImage(filename, R, G, B);
                Shuffle(R, G, B);
                SaveImage("Shuffle", R, G, B);
                printf("\"Shuffle\" operation is done!\n");
                break;
            case 8:
                if(strlen(filename) == 0){
                    printf("Load an image first.\n");
                    break;
                }
                LoadImage(filename, R, G, B);
                VFlip(R, G, B);
                SaveImage("vflip", R, G, B);
                printf("\"VFlip\" operation is done!\n");
                break;
            case 9:
                if(strlen(filename) == 0){
                    printf("Load an image first.\n");
                    break;
                }
                LoadImage(filename, R, G, B);
                HMirror(R, G, B);
                SaveImage("hmirror", R, G, B);
                printf("\"HMirror\" operation is done!\n");
                break;
            case 10:
                if(strlen(filename) == 0){
                    printf("Load an image first.\n");
                    break;
                }
                printf("Enter block size: ");
                scanf("%d", &block_size);
                LoadImage(filename, R, G, B);
                Pixelate(R, G, B, block_size);
                SaveImage("pixelate", R, G, B);
                printf("\"Pixelate\" operation is done!\n");
                break;
            case 11:
                AutoTest(R, G, B);
                break;
            default:
                break;
        }
        if(option == 12){
            break;
        }
    }
    /* End of replacing */
    return 0;
}
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char Type[SLEN];
    int  Width, Height, MaxValue;
    int  x, y;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\" for reading!\n", fname);
        return 1;
    }
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
        printf("\nUnsupported file format!\n");
        return 2;
    }
    fscanf(File, "%d", &Width);
    if (Width != WIDTH) {
        printf("\nUnsupported image width %d!\n", Width);
        return 3;
    }
    fscanf(File, "%d", &Height);
    if (Height != HEIGHT) {
        printf("\nUnsupported image height %d!\n", Height);
        return 4;
    }
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
        return 5;
    }
    if ('\n' != fgetc(File)) {
        printf("\nCarriage return expected!\n");
        return 6;
    }
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read successfully!\n", fname_ext);
    fclose(File);
    return 0;
}
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char SysCmd[SLEN * 5];
    int  x, y;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "w");
    if (!File) {
        printf("\nCannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }
    }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved successfully. \n", fname_ext);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "~eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_ext);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored for viewing. \n", fname);

    return 0;
}
//Change a color image to Black&White
void BlackNWhite(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int avg;
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            //change the intensity value of each color; Red, Green, and Blue
            avg = (R[i][j] + G[i][j] + B[i][j]) / 3;
            R[i][j] = avg;
            G[i][j] = avg;
            B[i][j] = avg;
        }
    }
}
//Make a negative of an image 
void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            //subtract from the maximum value, 255
            R[i][j] = 255 - R[i][j];
            G[i][j] = 255 - G[i][j];
            B[i][j] = 255 - B[i][j];
        }
    }
}
//Color-Filter an image
void ColorFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], 
                int target_r, int target_g, int target_b, int threshold, int replace_r, int replace_g, int replace_b){
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            //set a boundary
            //if out of range, keep the current color
            if((R[i][j] >= target_r - threshold && R[i][j] <= target_r + threshold)
            && (G[i][j] >= target_g - threshold && G[i][j] <= target_g + threshold)
            && (B[i][j] >= target_b - threshold && B[i][j] <= target_b + threshold)){
                R[i][j] = replace_r;
                G[i][j] = replace_g;
                B[i][j] = replace_b;
            }
        }
    }
}
//Edge Detection
void Edge(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    unsigned char R_1[WIDTH][HEIGHT];
    unsigned char G_1[WIDTH][HEIGHT];
    unsigned char B_1[WIDTH][HEIGHT];
    //make a copy of RGB intensity 2d array
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            R_1[i][j] = R[i][j];
            G_1[i][j] = G[i][j];
            B_1[i][j] = B[i][j];
        }
    }
    int red, green, blue;
    //calculate every pixel except for image boundaries
    for(int i = 1; i < WIDTH-1; i++){
        for(int j = 1; j < HEIGHT-1; j++){
            //variable used to detect the edge
            red = (- R[i-1][j-1] - R[i-1][j] - R[i-1][j+1] - R[i][j-1] + 
                (8*R[i][j]) - R[i][j+1] - R[i+1][j-1] - R[i+1][j] - R[i+1][j+1]);
            green = (- G[i-1][j-1] - G[i-1][j] - G[i-1][j+1] - G[i][j-1] + 
                (8*G[i][j]) - G[i][j+1] - G[i+1][j-1] - G[i+1][j] - G[i+1][j+1]);
            blue = (- B[i-1][j-1] - B[i-1][j] - B[i-1][j+1] - B[i][j-1] + 
                (8*B[i][j]) - B[i][j+1] - B[i+1][j-1] - B[i+1][j] - B[i+1][j+1]);
            //Use a saturated arithmetic; keep the value in range between 0 and 255
            if(red < 0){
                R_1[i][j] = 0;
            } else if(red > 255){
                R_1[i][j] = 255;
            } else {
                R_1[i][j] = red;
            } 
            if(green < 0){
                G_1[i][j] = 0;
            } else if(green > 255){
                G_1[i][j] = 255;
            } else {
                G_1[i][j] = green;
            }
            if(blue < 0){
                B_1[i][j] = 0;
            } else if(blue > 255){
                B_1[i][j] = 255;
            } else {
                B_1[i][j] = blue;
            }
        } 
    }
    //Make a black boundary
    for (int i = 0; i < WIDTH; i++) {
        R_1[i][0] = G_1[i][0] = B_1[i][0] = 0; //Left edge
        R_1[i][HEIGHT-1] = G_1[i][HEIGHT-1] = B_1[i][HEIGHT-1] = 0; //Right edge
    }
    for (int i = 0; i < HEIGHT; i++) {
        R_1[0][i] = G_1[0][i] = B_1[0][i] = 0; //Top edge
        R_1[WIDTH-1][i] = G_1[WIDTH-1][i] = B_1[WIDTH-1][i] = 0; //Bottom edge
    }
    // Copy the processed values back to the original RGB arrays
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            R[i][j] = R_1[i][j];
            G[i][j] = G_1[i][j];
            B[i][j] = B_1[i][j];
        }
    }
}
//Shuffle an image
void Shuffle(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    int block_WIDTH = 128; // 512/4
    int block_HEIGHT = 72; // 288/4
    int pairs[8][2] = {{1, 16}, {2, 15}, {3, 14}, {4, 13}, 
                       {5, 12}, {6, 11}, {7, 10}, {8, 9}};
    //Coordinate of Each Element in pairs 2D array
    //{1=(0,0), 16=(1,0)}, {2=(2,0), 15=(3,0)}, {2=(4,0), 15=(5,0)}, {2=(6,0), 15=(7,0)}
    //{2=(0,0), 15=(1,1)}, {2=(2,1), 15=(3,1)}, {2=(4,1), 15=(5,1)}, {2=(6,1), 15=(7,1)}
    for(int n = 0; n < 8; n++){
        int B1 = pairs[n][0] - 1;
        int B2 = pairs[n][1] - 1; 
        //WIDTH_STARTING_PTS  = (0 or 128 or 256 or 384)
        //HEIGHT_STARTING_PTS = (0 or 72 or 144 or 216)
        int x1_pt = (B1 % 4) * block_WIDTH;
        int y1_pt = (B1 / 4) * block_HEIGHT;
        int x2_pt = (B2 % 4) * block_WIDTH;
        int y2_pt = (B2 / 4) * block_HEIGHT;
        for(int i = 0; i < block_WIDTH; i++){
            for(int j = 0; j < block_HEIGHT; j++){
                //set vertical&horizontal starting point
                int x1 = i + x1_pt;
                int y1 = j + y1_pt;
                int x2 = i + x2_pt;
                int y2 = j + y2_pt;
                //swap the pairs
                //swap R value
                unsigned char temp1 = R[x1][y1];
                R[x1][y1] = R[x2][y2];
                R[x2][y2] = temp1;
                //swap G value
                unsigned char temp2 = G[x1][y1];
                G[x1][y1] = G[x2][y2];
                G[x2][y2] = temp2;
                //swap B value
                unsigned char temp3 = B[x1][y1];
                B[x1][y1] = B[x2][y2];
                B[x2][y2] = temp3;
            }
        }
    }
}
//Flip an image vertically
void VFlip(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    //Pairs to swap: (0,0) & (0,287), (0,1) & (0,286), and so on
    //Swap only vertical index j
    for(int j = 0; j < HEIGHT / 2; j++){
        for(int i = 0; i < WIDTH; i++){
            //swap R value
            unsigned char temp1 = R[i][j];
            R[i][j] = R[i][HEIGHT - 1 - j];
            R[i][HEIGHT - 1 - j] = temp1;
            //swap G value
            unsigned char temp2 = G[i][j];
            G[i][j] = G[i][HEIGHT - 1 - j];
            G[i][HEIGHT - 1 - j] = temp2;
            //swap B value
            unsigned char temp3 = B[i][j];
            B[i][j] = B[i][HEIGHT - 1 - j];
            B[i][HEIGHT - 1 - j] = temp3;
        }
    }
}
//Mirror an image horizontally
void HMirror(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    for(int i = 0; i < WIDTH; i++){
        for(int j = 0; j < HEIGHT; j++){
            //(0,0) = (0,255), (1,254), and so on..
            //[width - 1 - i] = _[i][j] so that the left half image is mirrored; not the right half
            R[WIDTH - 1 - i][j] = R[i][j];
            G[WIDTH - 1 - i][j] = G[i][j];
            B[WIDTH - 1 - i][j] = B[i][j];
        }
    }
}
//Pixelate an image with a desired block size
void Pixelate(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]
             ,int block_size){
    for(int i = 0; i < WIDTH; i+=block_size){
        for(int j = 0; j < HEIGHT; j+=block_size){
            int R_sum = 0, G_sum = 0, B_sum = 0;
            int count = 0;
            //Calculate the average RGB value in each block
            for(int x = i; x < i + block_size && x < WIDTH; x++){
                for(int y = j; y < j + block_size && y < HEIGHT; y++){
                    R_sum += R[x][y];
                    G_sum += G[x][y];
                    B_sum += B[x][y];
                    count++;
                }
            }
            unsigned char R_avg = R_sum / count;
            unsigned char G_avg = G_sum / count;
            unsigned char B_avg = B_sum / count;

            for(int x = i; x < i + block_size && x < WIDTH; x++){
                for(int y = j; y < j + block_size && y < HEIGHT; y++){
                    R[x][y] = R_avg;
                    G[x][y] = G_avg;
                    B[x][y] = B_avg;
                }
            }
        }
    }
}
//Test all functions in one shot
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
    char fname[SLEN] = "EngPlaza";

    LoadImage(fname, R, G, B);
    BlackNWhite(R, G, B);
    SaveImage("bw", R, G, B);
    printf("Black and White tested!\n\n");

    LoadImage(fname, R, G, B);
    Negative(R, G, B);
    SaveImage("negative", R, G, B);
    printf("Negative tested!\n\n");
    
    LoadImage(fname, R, G, B);
    ColorFilter(R, G, B, 130, 130, 150, 30, 0, 255, 255);
    SaveImage("colorfilter", R, G, B);
    printf("Color Filter tested!\n\n");

    LoadImage(fname, R, G, B);
    Edge(R, G, B);
    SaveImage("edge", R, G, B);
    printf("Edge tested!\n\n");

    LoadImage(fname, R, G, B);
    Shuffle(R, G, B);
    SaveImage("shuffle", R, G, B);
    printf("Shuffle tested!\n\n");
    
    LoadImage(fname, R, G, B);
    VFlip(R, G, B);
    SaveImage("vflip", R, G, B);
    printf("VFlip tested!\n\n");

    LoadImage(fname, R, G, B);
    HMirror(R, G, B);
    SaveImage("hmirror", R, G, B);
    printf("HMirror tested!\n\n");

    LoadImage(fname, R, G, B);
    Pixelate(R, G, B, 4);
    SaveImage("pixelate", R, G, B);
    printf("Pixelate tested!\n\n");
}
/*DO NOT EDIT AUTOTEST*/
/*DO NOT EDIT AUTOTEST*/
/*
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) {
        char fname[SLEN] = "EngPlaza";
        char sname[SLEN];

        LoadImage(fname, R, G, B);
        Negative(R, G, B);
        strcpy(sname, "negative");
        SaveImage(sname, R, G, B);
        printf("Negative tested!\n\n");

        LoadImage(fname, R, G, B);
        ColorFilter(R, G, B, 130, 130, 150, 30, 0, 255, 255);

        strcpy(sname, "colorfilter");
        SaveImage(sname, R, G, B);
        printf("Color Filter tested!\n\n");

        LoadImage(fname, R, G, B);
        Edge(R, G, B);
        strcpy(sname, "edge");
        SaveImage(sname, R, G, B);
        printf("Edge Detection tested!\n\n");

        LoadImage(fname, R, G, B);
        HMirror(R, G, B);
        strcpy(sname, "hmirror");
        SaveImage(sname, R, G, B);
        printf("HMirror tested!\n\n");

        LoadImage(fname, R, G, B);
        AddBorder (R, G, B, "pink", 32);
        strcpy(sname, "border");
        SaveImage(sname, R, G, B);
        printf("Border tested!\n\n");

        LoadImage(fname, R, G, B);
        BlackNWhite(R, G, B);
        strcpy(sname, "bw");
        SaveImage(sname, R, G, B);
        printf("Black & White tested!\n\n");

        LoadImage(fname, R, G, B);
        VFlip(R, G, B);
        strcpy(sname, "vflip");
        SaveImage(sname, R, G, B);
        printf("VFlip tested!\n\n");

        LoadImage(fname, R, G, B);
        Shuffle(R, G, B);
        strcpy(sname, "shuffle");
        SaveImage(sname, R, G, B);
        printf("Shuffle tested!\n\n");

        LoadImage(fname, R, G, B);
        Pixelate(R, G, B, 4);
        strcpy(sname, "pixelate");
        SaveImage("pixelate", R, G, B);
        printf("Pixelate tested!\n\n");
}
*/

/**************************************************************/
/* Please add your function definitions here...               */
/**************************************************************/

/* EOF */
