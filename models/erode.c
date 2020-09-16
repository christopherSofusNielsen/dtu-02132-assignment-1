#include "erode.h"

//Local
UCHAR erodePixel(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);


unsigned int erodeImage(UCHAR image[BMP_WIDTH][BMP_HEIGTH], UCHAR erodeImage[BMP_WIDTH][BMP_HEIGTH]){
    long int whitePixels=0;
    //loop over each pixel, insert erode result at same index in erodeImage
    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        for (int ih = 0; ih < BMP_HEIGTH; ih++)
        {
            UCHAR erodedPixel=erodePixel(image, iw, ih);
            erodeImage[iw][ih]=erodedPixel;
            if(erodedPixel>0){
                whitePixels++;
            }
        }
        
    }
    return whitePixels;
}

UCHAR erodePixel(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih){
    if(image[iw][ih]==0){
        return 0;
    }

    UCHAR result=0;
    //left 
    result+=(iw==0)?255:image[iw-1][ih];
    result+=(ih==0)?255:image[iw][ih-1];
    result+=(iw<BMP_WIDTH-1)?image[iw+1][ih]:255;
    result+=(ih<BMP_HEIGTH-1)?image[iw][ih+1]:255;
    
    return (result==1000)?255:0;
}