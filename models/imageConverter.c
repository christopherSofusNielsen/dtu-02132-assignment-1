#include "imageConverter.h"

#include <stdio.h>

//locals
UCHAR getMean(UCHAR rbgValues[]);
UCHAR compareThreshold(UCHAR val);

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

void grayscaleToBlackWhite(UCHAR image[BMP_WIDTH][BMP_HEIGTH]){
    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        for (int ih = 0; ih < BMP_HEIGTH; ih++)
        {
            image[iw][ih]=compareThreshold(image[iw][ih]);
        }
    }
}

void digitalToAnalog(UCHAR digital_image[BMP_WIDTH][BMP_HEIGTH], 
UCHAR analog_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]){
    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        for (int ih = 0; ih < BMP_HEIGTH; ih++)
        {
            UCHAR val=digital_image[iw][ih];
            
            for (UCHAR i = 0; i < 3; i++)
            {
                analog_image[iw][ih][i]=val;
            }            
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

UCHAR compareThreshold(UCHAR val){
    return val<GRAYSCALE_THRESHOLD?0:255;
}
