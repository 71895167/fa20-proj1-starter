/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

uint8_t evaluate8bits(uint8_t cur, uint8_t *arr, uint32_t rule) {
    uint8_t ret = 0;
    for (int i = 0; i < 8; i++) {
        int cur_bit = (cur >> i) & 1;
        int bit_sum = 0; for (int j = 0; j < 8; j++) bit_sum += (arr[j] >> i) & 1;
        int life = (rule >> (9*cur_bit + bit_sum)) & 1;
        ret += (life << i);
    }
    return ret;
}
//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
    uint8_t Rs[8], Gs[8], Bs[8];
    Color *ret = (Color *) malloc(sizeof(Color));
    Color *cur = image->image[row * image->cols + col];
    for (int c = 0, di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if ( ! (di == 0 && dj == 0)) { // 本来想把c++写在dj++后面的
                int i = (row + di + image->rows) % image->rows;
                int j = (col + dj + image->cols) % image->cols;
                Color *color = image->image[i * image->cols + j];
                Rs[c] = color->R, Gs[c] = color->G, Bs[c] = color->B;
                c++;
            }
        }
    }
    ret->R = evaluate8bits(cur->R, Rs, rule);
    ret->G = evaluate8bits(cur->G, Gs, rule);
    ret->B = evaluate8bits(cur->B, Bs, rule);
    return ret;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
    Image *ret = (Image *) malloc(sizeof(Image));
    ret->cols = image->cols;  ret->rows = image->rows;
    ret->image = (Color **) malloc(ret->rows * ret->cols * sizeof(Color *));
    for (int i = 0; i < ret->rows; i++) {
        for (int j = 0; j < ret->cols; j++) {
            Color *tmp = evaluateOneCell(image, i, j, rule);
            ret->image[i*ret->cols + j] = tmp;
            int a = 1;
            a++;
        }
    }
    return ret;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
    char *fn = argv[1];
//    uint32_t rule = strtol(argv[2] + 2, NULL, 16);
    uint32_t rule = strtol(argv[2], NULL, 0);
//    printf("rule: %" PRIu32 "\n", rule);
    Image *image = readData(fn);
    Image *next = life(image, rule);
    writeData(next);
    freeImage(image);  freeImage(next);
    return 0;
}
