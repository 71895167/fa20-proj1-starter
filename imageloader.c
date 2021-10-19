/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
    char P3[20];  int n255;
    FILE *fp = fopen(filename, "r");
    Image *img = (Image *) malloc(sizeof(Image));
    
    fscanf(fp, "%s\n%d %d\n%d\n", P3, &(img->cols), &(img->rows), &n255);
    img->image = (Color **) malloc(img->rows * img->cols * sizeof(Color *));
    for (int i = 0; i < img->rows; i++) {
        for (int j = 0; j < img->cols; j++) {
            // int R, G, B;
            Color *c = (Color *) malloc(sizeof(Color));
            fscanf(fp, "%" SCNu8 " %" SCNu8 " %" SCNu8, &(c->R), &(c->G), &(c->B));
            *(img->image + i*(img->cols) + j) = c;
        }
    }
    fclose(fp);
    return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
    printf("P3\n%d %d\n255\n", image->cols, image->rows);
    for (int i = 0; i < image->rows; i++) {
        for (int j = 0; j < image->cols; j++) {
            printf(j == 0 ? "%3d %3d %3d" : "   %3d %3d %3d", 
                    image->image[i*image->cols + j]->R, 
                    image->image[i*image->cols + j]->G, 
                    image->image[i*image->cols + j]->B);
        }
        printf("\n");
    }
}

//Frees an image
void freeImage(Image *image)
{
    for (int i = 0; i < image->rows * image->cols; i++) {
        free(*(image->image + i));
    }
    free(image->image);
    free(image);
}
