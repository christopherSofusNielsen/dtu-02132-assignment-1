#if !defined(IMAGE_CONVERTER_H)
#define IMAGE_CONVERTER_H
#include "../utilities/cbmp.h"
#include "../utilities/types.h"
#include "../utilities/parameters.h"
#include <string.h>
#include "../utilities/list.h"

void rgbToGrayscale(UCHAR image_array[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], UCHAR grayscale_image[BMP_WIDTH][BMP_HEIGTH]);

void grayscaleToBlackWhiteOtsu(UCHAR image[BMP_WIDTH][BMP_HEIGTH]);

void digitalToAnalog(UCHAR digital_image[BMP_WIDTH][BMP_HEIGTH], UCHAR analog_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS]);

void printPoints(node_t **points_head);

void printResult(node_t **points_head);

void addMarkersToAnalogImage(UCHAR image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], node_t **points_head);

#endif // IMAGE_CONVERTER_H
