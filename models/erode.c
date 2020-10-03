#include "erode.h"

#include <stdio.h>

//Local
UCHAR erodePixelSafely(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);
PIXEL_STATE erodePixelFast(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);

unsigned long int erodeImage(UCHAR image[BMP_WIDTH][BMP_HEIGTH], UCHAR erodeImage[BMP_WIDTH][BMP_HEIGTH])
{
    unsigned long int whitePixels = 0;

    //Create safe area
    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        UCHAR erodedPixel;
        //TOP
        erodedPixel = erodePixelSafely(image, iw, 0);
        erodeImage[iw][0] = erodedPixel;
        if (erodedPixel > 0)
        {
            whitePixels++;
        }

        //BOTTOM
        erodedPixel = erodePixelSafely(image, iw, BMP_HEIGTH_EDGE);
        erodeImage[iw][BMP_HEIGTH_EDGE] = erodedPixel;
        if (erodedPixel > 0)
        {
            whitePixels++;
        }
    }

    for (int ih = 0; ih < BMP_HEIGTH; ih++)
    {
        UCHAR erodedPixel;
        //LEFT
        erodedPixel = erodePixelSafely(image, 0, ih);
        erodeImage[0][ih] = erodedPixel;
        if (erodedPixel > 0)
        {
            whitePixels++;
        }

        //RIGHT
        erodedPixel = erodePixelSafely(image, BMP_WIDTH_EDGE, ih);
        erodeImage[BMP_WIDTH_EDGE][ih] = erodedPixel;
        if (erodedPixel > 0)
        {
            whitePixels++;
        }
    }

    for (int iw = 1; iw < BMP_WIDTH_EDGE; iw++)
    {
        for (int ih = 1; ih < BMP_HEIGTH_EDGE; ih++)
        {
            PIXEL_STATE erodedPixel = erodePixelFast(image, iw, ih);
            if (ih + 1 < BMP_HEIGTH_EDGE && erodedPixel == BLACK)
            {
                //set this pixel and the next to black and increment ih - so the next pixel is skipped
                erodeImage[iw][ih] = 0;
                ih++;
                erodeImage[iw][ih] = 0;
                continue;
            }
            else if (ih + 2 < BMP_HEIGTH_EDGE && erodedPixel == NEXT_BLACK)
            {
                //set this pixel, and the two next pixels to black and increment ih twice - so the next two pixels are skipped
                erodeImage[iw][ih] = 0;
                ih++;
                erodeImage[iw][ih] = 0;
                ih++;
                erodeImage[iw][ih] = 0;
                continue;
            }
            if (erodedPixel == WHITE)
            {
                //set this pixel to white and don't skip the next one, because it could be white too
                erodeImage[iw][ih] = 255;
                whitePixels++;
            }
            else
            {
                //if the scope (the array legth) did not allow to skip the next pixel, then just make this one black
                //and make loop handle the rest
                erodeImage[iw][ih] = 0;
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

UCHAR erodePixelSafely(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih)
{
    if (image[iw][ih] == 0)
    {
        return 0;
    }
    //if all pixel are white, this will be them sum, so res=0 when done, we know that the pixel should be white
    int res = 2040;

    //left
    res -= (iw == 0 || ih == 0) ? 255 : image[iw - 1][ih - 1];
    res -= (iw == 0) ? 255 : image[iw - 1][ih];
    res -= (iw == 0 || ih >= BMP_HEIGTH_EDGE) ? 255 : image[iw - 1][ih + 1];

    //top bottom
    res -= (ih == 0) ? 255 : image[iw][ih - 1];
    res -= (ih < BMP_HEIGTH_EDGE) ? image[iw][ih + 1] : 255;

    //right
    res -= (iw < BMP_WIDTH_EDGE && ih >= 0) ? image[iw + 1][ih] : 255;
    res -= (iw < BMP_WIDTH_EDGE) ? image[iw + 1][ih] : 255;
    res -= (iw < BMP_WIDTH_EDGE && ih >= BMP_HEIGTH_EDGE) ? image[iw + 1][ih] : 255;

    return (res) ? 0 : 255;
}

/*
Assume pixel is white if outside image. 
Box:
1 1 1
1 1 1
1 1 1
*/

PIXEL_STATE erodePixelFast(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih)
{
    if (image[iw][ih + 1] == 0)
    {
        return NEXT_BLACK;
    }
    if (image[iw][ih] == 0)
    {
        return BLACK;
    }
    //if all pixel are white, this will be them sum, so res=0 when done we know that hte pixel should be white
    int res = 1785; //7*255=1785

    res -= image[iw - 1][ih - 1];
    res -= image[iw - 1][ih];
    res -= image[iw - 1][ih + 1];
    res -= image[iw][ih - 1];
    //res -= image[iw][ih + 1]; this must be white otherwise we would not be here, because of first if-statement
    res -= image[iw + 1][ih - 1];
    res -= image[iw + 1][ih];
    res -= image[iw + 1][ih + 1];

    return (res) ? BLACK : WHITE;
}