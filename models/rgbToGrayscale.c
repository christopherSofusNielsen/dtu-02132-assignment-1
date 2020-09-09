#include "rgbToGrayscale.h"

#include <stdio.h>

//locals
UCHAR getMean(UCHAR rbgValues[]);

void rgbToGrayscale(UCHAR image_array[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], 
UCHAR grayscale_image[BMP_WIDTH][BMP_HEIGTH]){

    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        for (int ih = 0; ih < BMP_HEIGTH; ih++)
        {
            UCHAR mean=getMean(image_array[iw][ih]);
            grayscale_image[iw][ih]=mean;
        }
    }
    
}

UCHAR getMean(UCHAR rbgValues[]){
    int sum=0;

    for (UCHAR i = 0; i < 3; i++)
    {
        sum+=rbgValues[i];    
    }

    return sum/3;
}

