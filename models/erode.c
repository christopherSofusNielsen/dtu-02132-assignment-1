#include "erode.h"

#include <stdio.h>

//Local
//UCHAR erodePixel(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);
UCHAR erodePixel2(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);
UCHAR erodePixel2fast(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);


unsigned long int erodeImage(UCHAR image[BMP_WIDTH][BMP_HEIGTH], UCHAR erodeImage[BMP_WIDTH][BMP_HEIGTH]){
    unsigned long int whitePixels=0;

    //Create safe area
    for (int iw = 0; iw < BMP_WIDTH; iw++){
        UCHAR erodedPixel;
        //TOP
        erodedPixel=erodePixel2(image, iw, 0);
        erodeImage[iw][0]=erodedPixel;
        if(erodedPixel>0){
            whitePixels++;
        }

        //BOTTOM
        erodedPixel=erodePixel2(image, iw, BMP_HEIGTH_EDGE);
        erodeImage[iw][BMP_HEIGTH_EDGE]=erodedPixel;
        if(erodedPixel>0){
            whitePixels++;
        }
    }

    for (int ih = 0; ih < BMP_HEIGTH; ih++){
        UCHAR erodedPixel;
        //LEFT
        erodedPixel=erodePixel2(image, 0, ih);
        erodeImage[0][ih]=erodedPixel;
        if(erodedPixel>0){
            whitePixels++;
        }

        //RIGHT
        erodedPixel=erodePixel2(image, BMP_WIDTH_EDGE, ih);
        erodeImage[BMP_WIDTH_EDGE][ih]=erodedPixel;
        if(erodedPixel>0){
            whitePixels++;
        }
    }



    //loop over each pixel, insert erode result at same index in erodeImage
    for (int iw = 1; iw < BMP_WIDTH_EDGE; iw++)
    {
        for (int ih = 1; ih < BMP_HEIGTH_EDGE; ih++)
        {
            UCHAR erodedPixel=erodePixel2fast(image, iw, ih);
            erodeImage[iw][ih]=erodedPixel;
            if(erodedPixel>0){
                whitePixels++;
            }else if(ih+1<BMP_HEIGTH){
                ih++;
                erodeImage[iw][ih]=0;
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
    //if all pixel are white, this will be them sum, so res=0 when done we know that hte pixel should be white
    int res=2040;
        
    //left
    res-=(iw==0 || ih==0)?255:image[iw-1][ih-1];
    res-=(iw==0)?255:image[iw-1][ih];
    res-=(iw==0 || ih>=BMP_HEIGTH_EDGE)?255:image[iw-1][ih+1];
    
    //top bottom
    res-=(ih==0)?255:image[iw][ih-1];
    res-=(ih<BMP_HEIGTH_EDGE)?image[iw][ih+1]:255; 
    
    //right
    res-=(iw<BMP_WIDTH_EDGE && ih>=0)?image[iw+1][ih]:255;
    res-=(iw<BMP_WIDTH_EDGE)?image[iw+1][ih]:255;
    res-=(iw<BMP_WIDTH_EDGE && ih>=BMP_HEIGTH_EDGE)?image[iw+1][ih]:255;

    return (res)?0:255;
}

UCHAR erodePixel2fast(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih){
    if(image[iw][ih]==0){
        return 0;
    }
    //if all pixel are white, this will be them sum, so res=0 when done we know that hte pixel should be white
    int res=2040;
    
    res-=image[iw-1][ih-1];
    res-=image[iw-1][ih];
    res-=image[iw-1][ih+1];
    res-=image[iw][ih-1];
    res-=image[iw][ih+1];
    res-=image[iw+1][ih-1];
    res-=image[iw+1][ih];
    res-=image[iw+1][ih+1];

    return (res)?0:255;
}

/*
Assume pixel is white if outside image. 
Box:
0 1 0
1 1 1
0 1 0
*/

// UCHAR erodePixel(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih){
//     if(image[iw][ih]==0){
//         return 0;
//     }

//     int result=0;
//     result+=(iw==0)?255:image[iw-1][ih];
//     result+=(ih==0)?255:image[iw][ih-1];
//     result+=(iw<BMP_WIDTH-1)?image[iw+1][ih]:255;
//     result+=(ih<BMP_HEIGTH-1)?image[iw][ih+1]:255; 
   
//     return (result>1000)?255:0;
// }
