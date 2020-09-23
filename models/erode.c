#include "erode.h"

#include <stdio.h>

//Local
UCHAR erodePixel(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);
UCHAR erodePixel2(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);


unsigned long int erodeImage(UCHAR image[BMP_WIDTH][BMP_HEIGTH], UCHAR erodeImage[BMP_WIDTH][BMP_HEIGTH]){
    unsigned long int whitePixels=0;
    //loop over each pixel, insert erode result at same index in erodeImage
    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        for (int ih = 0; ih < BMP_HEIGTH; ih++)
        {
            UCHAR erodedPixel=erodePixel2(image, iw, ih);
            erodeImage[iw][ih]=erodedPixel;
            if(erodedPixel>0){
                whitePixels++;
            }
        }
        
    }
    return whitePixels;
}


/*
Assume pixel is white if outside image. 
Box:
1 1 1
1 1 1
1 1 1
*/

UCHAR erodePixel2(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih){
    if(image[iw][ih]==0){
        return 0;
    }

    int result=0;
    //left
    result+=(iw==0 || ih==0)?255:image[iw-1][ih-1];
    result+=(iw==0)?255:image[iw-1][ih];
    result+=(iw==0 || ih>=BMP_HEIGTH-1)?255:image[iw-1][ih+1];
    
    //top bottom
    result+=(ih==0)?255:image[iw][ih-1];
    result+=(ih<BMP_HEIGTH-1)?image[iw][ih+1]:255; 
    
    //right
    result+=(iw<BMP_WIDTH-1 && ih>=0)?image[iw+1][ih]:255;
    result+=(iw<BMP_WIDTH-1)?image[iw+1][ih]:255;
    result+=(iw<BMP_WIDTH-1 && ih>=BMP_HEIGTH-1)?image[iw+1][ih]:255;
   
    return (result>=8*255)?255:0;
}

/*
Assume pixel is white if outside image. 
Box:
0 1 0
1 1 1
0 1 0
*/

UCHAR erodePixel(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih){
    if(image[iw][ih]==0){
        return 0;
    }

    int result=0;
    result+=(iw==0)?255:image[iw-1][ih];
    result+=(ih==0)?255:image[iw][ih-1];
    result+=(iw<BMP_WIDTH-1)?image[iw+1][ih]:255;
    result+=(ih<BMP_HEIGTH-1)?image[iw][ih+1]:255; 
   
    return (result>1000)?255:0;
}
