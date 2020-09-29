#include "imageConverter.h"

#include <stdio.h>

//locals
UCHAR getMean(UCHAR rbgValues[]);
UCHAR compareThreshold(UCHAR val);
UCHAR compareThreshold2(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);
void printNumberOfPoints(int nPoints);

void rgbToGrayscale(UCHAR image_array[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS],
                    UCHAR grayscale_image[BMP_WIDTH][BMP_HEIGTH])
{

    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        for (int ih = 0; ih < BMP_HEIGTH; ih++)
        {
            grayscale_image[iw][ih] = getMean(image_array[iw][ih]);
        }
    }
}

void grayscaleToBlackWhite(UCHAR image[BMP_WIDTH][BMP_HEIGTH])
{
    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        for (int ih = 0; ih < BMP_HEIGTH; ih++)
        {
            //image[iw][ih]=compareThreshold2(image, iw, ih);

            //image[iw][ih]=compareThreshold(image[iw][ih]);
            image[iw][ih] = image[iw][ih] < GRAYSCALE_THRESHOLD ? 0 : 255;
        }
    }
}

void grayscaleToBlackWhiteOtsu(UCHAR image[BMP_WIDTH][BMP_HEIGTH])
{
    UCHAR newImage[BMP_WIDTH][BMP_HEIGTH];
    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        for (int ih = 0; ih < BMP_HEIGTH; ih++)
        {
            newImage[iw][ih] = compareThreshold2(image, iw, ih);
        }
    }
    memcpy(image, newImage, sizeof(newImage));
}

void digitalToAnalog(UCHAR digital_image[BMP_WIDTH][BMP_HEIGTH],
                     UCHAR analog_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS])
{
    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        for (int ih = 0; ih < BMP_HEIGTH; ih++)
        {
            UCHAR val = digital_image[iw][ih];

            for (UCHAR i = 0; i < 3; i++)
            {
                analog_image[iw][ih][i] = val;
            }
        }
    }
}
void addMarkersToAnalogImage(UCHAR image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS], node_t **points_head)
{
    node_t *tmp = *points_head;
    while (tmp != NULL)
    {
        int x = tmp->x;
        int y = tmp->y;

        int yWidth = (y + 1 > BMP_HEIGTH - 1) ? y : y + 1;
        int wHeigth = (x + 1 > BMP_WIDTH - 1) ? x : x + 1;

        //draw row
        int rowStart = (x - CROSS_R_SIZE < 0) ? 0 : x - CROSS_R_SIZE;
        int rowEnd = (x + CROSS_R_SIZE > BMP_WIDTH - 1) ? BMP_WIDTH - 1 : x + CROSS_R_SIZE;

        for (int iw = rowStart; iw <= rowEnd; iw++)
        {
            image[iw][y][0] = 255;
            image[iw][y][1] = 0;
            image[iw][y][2] = 0;
            image[iw][yWidth][0] = 255;
            image[iw][yWidth][1] = 0;
            image[iw][yWidth][2] = 0;
        }

        //draw col
        int colStart = (y - CROSS_R_SIZE < 0) ? 0 : y - CROSS_R_SIZE;
        int colEnd = (y + CROSS_R_SIZE > BMP_HEIGTH - 1) ? BMP_HEIGTH - 1 : y + CROSS_R_SIZE;

        for (int ih = colStart; ih <= colEnd; ih++)
        {
            image[x][ih][0] = 255;
            image[x][ih][1] = 0;
            image[x][ih][2] = 0;
        }
        tmp = tmp->next;
    }
}

UCHAR getMean(UCHAR rbgValues[])
{
    int sum = 0;

    /*
    This is faster than initialize a for loop
    */
    sum += rbgValues[0];
    sum += rbgValues[1];
    sum += rbgValues[2];

    return sum >> 2;
}

UCHAR compareThreshold(UCHAR val)
{
    return val < GRAYSCALE_THRESHOLD ? 0 : 255;
}

UCHAR compareThreshold2(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih)
{
    if (iw == 0 || iw == BMP_WIDTH - 1 || ih == 0 || ih == BMP_HEIGTH)
    {
        return compareThreshold(image[iw][ih]);
    }

    int sum = 0;

    //sum += image[iw][ih];
    sum += image[iw][ih - 1];
    sum += image[iw][ih + 1];
    sum += image[iw - 1][ih];
    sum += image[iw + 1][ih];

    //bigger form
    sum += image[iw - 1][ih - 1];
    sum += image[iw - 1][ih + 1];
    sum += image[iw + 1][ih - 1];
    sum += image[iw + 1][ih + 1];

    int avr = sum / 8;

    if (avr < OTSU_MIN || avr >= OTSU_MAX)
    {
        return compareThreshold(image[iw][ih]);
    }

    return image[iw][ih] <= avr ? 0 : 255;
}

void printPoints(node_t **points_head)
{
    node_t *tmp = *points_head;
    unsigned int nPoints = 0;
    while (tmp != NULL)
    {
        printf("X: %d\tY: %d\n", tmp->x, tmp->y);
        tmp = tmp->next;
        nPoints++;
    }
    printf("\n");

    printf("---------------------------------\n");
    printf("Number of points: %d\n", nPoints);
    printf("---------------------------------\n\n");
}

void printResult(node_t **points_head)
{
    node_t *tmp = *points_head;
    unsigned int nPoints = 0;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        nPoints++;
    }
    printNumberOfPoints(nPoints);
}

void printNumberOfPoints(int nPoints)
{
    printf("---------------------------------\n");
    printf("Number of points: %d\n", nPoints);
    printf("---------------------------------\n\n");
}
