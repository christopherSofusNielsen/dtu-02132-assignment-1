#if !defined(IMAGE_CONVERTER_H)
#define IMAGE_CONVERTER_H
#include "../utilities/cbmp.h"
#include "../utilities/types.h"
#include "../utilities/parameters.h"

void rgbToGrayscale(UCHAR image_array[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], UCHAR grayscale_image[BMP_WIDTH][BMP_HEIGTH]);

void grayscaleToBlackWhite(UCHAR grayscale_image[BMP_WIDTH][BMP_HEIGTH]);
#endif // IMAGE_CONVERTER_H
