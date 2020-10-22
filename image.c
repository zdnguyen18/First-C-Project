/** CS310 Project 1
File: image.c
Name: Uyen Nguyen 
Date: 17th Oct
Collaboration Declaration: assistance received from Pyone
*/
#include <stdio.h>
#include <stdlib.h>
//Part 1.1: image <image_input_file> <negative_image_filename> 
int ind(int r, int c, int n_cols) {
  return r * n_cols + c;
}
int main(int argc, char**argv) 
{  
    int r =0,c = 0; //row~height; col ~width
    // file pointer to store image file 
    FILE *pgmfile, *negative_pgmfile, *rotate_pgmfile;
  
    // Open an image file 
    pgmfile = fopen(argv[1], "r"); 
      
    // Open an negative image file //argv[2] = negative_image_file
    negative_pgmfile = fopen(argv[2], "w"); 
    int height, width;
    //scan every number before the role & column (fscanf: read file)
    fscanf(pgmfile, "P2\n%d %d\n255\n", &width, &height);
    //define 2d array name is orignal (essential for fscanf)
    int *original = malloc(sizeof(int)*height*width);
    //for loop to put value into the 2D array
    //scan over the input original pgm -> col & row
    for(r = 0; r < height; r++) {
        for(c = 0; c < width; c++){
    //scanning the file one by one to assign the value row & col to the original file
            fscanf(pgmfile, "%d\n", &original[ind(r, c,width)]);
        }
    } 
    fclose(pgmfile);

    // Create negative PGM image using pixel value (fprintf: write file)

    fprintf(negative_pgmfile, "P2\n%d %d\n255\n", height, width); 
    //int r =0,c = 0; redefine & reset in the for loop 
    for(r = 0; r < height; r++) { 
        for(c = 0; c < width; c++){
            fprintf(negative_pgmfile, "%d\n", (255 - original[ind(r, c,width)])); 
        }
        fprintf(negative_pgmfile, "\n"); 
    } 
    fclose(negative_pgmfile); 

//Part 1.2: <rotate_image_filename>
    rotate_pgmfile = fopen(argv[3], "w");
    // Create right 90 degree rotate PGM image using pixel value
    fprintf(rotate_pgmfile, "P2\n%d %d\n255\n", width, height); 
    //int r =0,c = 0; redefine & reset in the for loop 
    for(int r = 0; r < width; r++) { 
        for(int c = 0 ; c < height; c++){
            //mirror [r][c] 
            //then rotate to the right [height-c-1] [r]
            //if left rotate then [c] [width-r-1]
            fprintf(rotate_pgmfile, "%d\n", original[ind(height- c -1,r,width)]); 
        }
        fprintf(rotate_pgmfile, "\n"); 
    } 
    fclose(rotate_pgmfile); 
    free(original);
}   

