/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
    Color *ret = (Color *) malloc(sizeof(Color));
    Color *color = image->image[row * image->cols + col];
    ret->R = ret->G = ret->B = 255 * (color->B % 2);
    return ret;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
    Image *ret = (Image *) malloc(sizeof(Image));
    ret->cols = image->cols;  ret->rows = image->rows;
    ret->image = (Color **) malloc(ret->rows * ret->cols * sizeof(Color *));
    for (int i = 0; i < ret->rows; i++) {
        for (int j = 0; j < ret->cols; j++) {
            ret->image[i * ret->cols + j] = evaluateOnePixel(image, i, j);
        }
    }
    return ret;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
    char *fn = argv[1];
    int len = strlen(fn);
    if (fn[len-1] != 'm' || fn[len-2] != 'p'
        || fn[len-3] != 'p' || fn[len-4] != '.') {
        return -1;
    }
    // malloc fails?? malloc主要是之前写的函数在做啊？

    Image *image = readData(fn);
    Image *stegane = steganography(image);
    writeData(stegane);
    freeImage(image);  freeImage(stegane);
    return 0;
}
