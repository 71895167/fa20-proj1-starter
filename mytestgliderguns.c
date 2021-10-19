#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imageloader.h"

// 写的有问题…算了，用shell脚本也不写了，就随便找两个试试吧
// diff ./studentOutputs/GliderGuns/GliderGuns_0x1808_10075.ppm ./testOutputs/GliderGuns/GliderGuns_0x1808_10075.ppm
int main(int arg, char **argv) {
    for (int i = 0; i <= 100; i++) {
        char mine[120], theirs[120];
        sprintf(mine, "./studentOutputs/GliderGuns/GliderGuns_0x1808_10%03d", i);
        sprintf(theirs,  "./testOutputs/GliderGuns/GliderGuns_0x1808_10%03d", i);
        Image *my_image = readData(mine), *their_image = readData(theirs);
        if (my_image->cols != their_image->cols || my_image->rows != their_image->rows) {
            printf("unmatched cols or rows, file number: %d\n", i);
            free(my_image);  free(their_image);
            return -1;
        }
        for (int i = 0; i < my_image->cols * my_image->rows; i++) {
            Color *my_color = my_image->image[i], *their_color = their_image->image[i];
            if (my_color->R != their_color->R ||
                  my_color->G != their_color->G ||
                  my_color->B != their_color->B) {
                printf("unmatched pixel, file number: %d\n", i);
                free(my_image);  free(their_image);
                return -1;
            }
        }
        free(my_image);  free(their_image);
    }
    return 0;
}   
