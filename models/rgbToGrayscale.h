#if !defined(RGB_TO_GRAYSCALE_H)
#define RGB_TO_GRAYSCALE_H
#include "../utilities/cbmp.h"
#include "../utilities/types.h"

void rgbToGrayscale(UCHAR image_array[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], UCHAR grayscale_image[BMP_WIDTH][BMP_HEIGTH]);


#endif // RGB_TO_GRAYSCALE_H
