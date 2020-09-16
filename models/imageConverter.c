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

void addMarkersToAnalogImage(UCHAR image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], POINT pnts[POINTS_LENGTH], int nPoints){
    for (int i = 0; i < nPoints; i++)
    {
        int x=pnts[i].x;
        int y=pnts[i].y;

        int yWidth=(y+1>BMP_HEIGTH-1)?y:y+1;
        int wHeigth=(x+1>BMP_WIDTH-1)?x:x+1;


        //draw row
        int rowStart=(x-CROSS_R_SIZE<0)?0:x-CROSS_R_SIZE;
        int rowEnd=(x+CROSS_R_SIZE>BMP_WIDTH-1)?BMP_WIDTH-1:x+CROSS_R_SIZE;
        
        for (int iw = rowStart; iw <= rowEnd; iw++)
        {
            image[iw][y][0]=255;
            image[iw][y][1]=0;
            image[iw][y][2]=0;
            image[iw][yWidth][0]=255;
            image[iw][yWidth][1]=0;
            image[iw][yWidth][2]=0;
        }

        //draw col
        int colStart=(y-CROSS_R_SIZE<0)?0:y-CROSS_R_SIZE;
        int colEnd=(y+CROSS_R_SIZE>BMP_HEIGTH-1)?BMP_HEIGTH-1:y+CROSS_R_SIZE;

        for (int ih = colStart; ih <= colEnd; ih++)
        {
            image[x][ih][0]=255;
            image[x][ih][1]=0;
            image[x][ih][2]=0;
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

void printPoints(POINT points[POINTS_LENGTH], int length){
    printf("\n\nList of points:\n\n");
    for (int i = 0; i < length; i++)
    {
        printf("X: %d\tY: %d\n", points[i].x, points[i].y);
    }
}

void printResult(int nPoints){
    printf("---------------------------------\n");
    printf("Number of points: %d\n", nPoints);
    printf("---------------------------------\n\n");
}
