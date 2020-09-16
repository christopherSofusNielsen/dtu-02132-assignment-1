#if !defined(IMAGE_CONVERTER_H)
#define IMAGE_CONVERTER_H
#include "../utilities/cbmp.h"
#include "../utilities/types.h"
#include "../utilities/parameters.h"
#include <string.h>

void rgbToGrayscale(UCHAR image_array[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], UCHAR grayscale_image[BMP_WIDTH][BMP_HEIGTH]);

void grayscaleToBlackWhite(UCHAR grayscale_image[BMP_WIDTH][BMP_HEIGTH]);

void grayscaleToBlackWhiteOtsu(UCHAR image[BMP_WIDTH][BMP_HEIGTH]);

void digitalToAnalog(UCHAR digital_image[BMP_WIDTH][BMP_HEIGTH], UCHAR analog_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);

void printPoints(POINT points[POINTS_LENGTH], int length);

void addMarkersToAnalogImage(UCHAR image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], POINT pnts[POINTS_LENGTH], int nPoints);

void printResult(int nPoints);

#endif // IMAGE_CONVERTER_H
