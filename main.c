#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "utilities/cbmp.h"
#include "utilities/states_enum.h"
#include "utilities/types.h"
#include "utilities/logger.h"
#include "utilities/list.h"

#include "models/imageConverter.h"
#include "models/erode.h"
#include "models/detectCells.h"
#include "models/filterCells.h"

//variabels
UCHAR input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
UCHAR output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];

UCHAR digi_buffer_0[BMP_WIDTH][BMP_HEIGTH];
UCHAR digi_buffer_1[BMP_WIDTH][BMP_HEIGTH];

// UCHAR binary_image_0[BMP_WIDTH][BMP_HEIGTH];
// UCHAR binary_image_1[BMP_WIDTH][BMP_HEIGTH];

// UCHAR (*digi_buffer_0)[BMP_HEIGTH] = binary_image_0;
// UCHAR (*digi_buffer_1)[BMP_HEIGTH] = binary_image_1;

unsigned long int whitePixels = 0;
int pointIndex = 0;
POINT points[POINTS_LENGTH];
int erodeCnt = 0;

//debug

void swap(UCHAR (**a)[BMP_WIDTH], UCHAR (**b)[BMP_WIDTH])
{
    UCHAR(*temp)
    [BMP_WIDTH] = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char *argv[])
{
    //State vars
    STATES state, nextState = INIT;
    BOOL run = TRUE;

    //list
    node_t *points_head = NULL;

    //debug
    char str[30] = {'\0'};

    //Time
    clock_t start, end, t0, t1;
    double cpu_time_used;

    while (run)
    {
        state = nextState;
        switch (state)
        {
        case INIT:
            info("Program start!");
            if (argc < 3)
            {
                fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
                nextState = EXIT;
            }
            else
            {
                nextState = LOAD_FILE;
            }
            break;

        case LOAD_FILE:
            //info("load file state");
            read_bitmap(argv[1], input_image);
            start = clock();
            nextState = RGB_TO_GRAY;
            break;

        case RGB_TO_GRAY:
            rgbToGrayscale(input_image, digi_buffer_0);
            nextState = GRAY_TO_BW;
            break;

        case GRAY_TO_BW:
            grayscaleToBlackWhite(digi_buffer_0);
            nextState = ERODE_IMAGE;
            break;

        case ERODE_IMAGE:
            t0 = clock();
            whitePixels = 0;
            whitePixels = erodeImage(digi_buffer_0, digi_buffer_1);
            //swap(&digi_buffer_0, &digi_buffer_1);
            memcpy(digi_buffer_0, digi_buffer_1, sizeof(digi_buffer_1));
            t1 = clock();
            cpu_time_used = ((double)(t1 - t0)) / CLOCKS_PER_SEC;
            printf("Erode time: %f s\n", cpu_time_used);
            nextState = INIT_ANALYSIS;
            break;

        case INIT_ANALYSIS:
            if (whitePixels == 0)
            {
                //nextState = FITLER_POINTS;
                nextState = MARK_POINTS;
            }
            else
            {
                //nextState = PRINT_ERODE_IMAGE;
                nextState = DETECT_CELLS;
            }
            break;

        case FITLER_POINTS:
            printf("Before points %d\n", pointIndex);
            removeOverlappingCells(points, &pointIndex);
            printf("After points %d\n", pointIndex);

            nextState = MARK_POINTS;
            break;

        case PRINT_ERODE_IMAGE:
            sprintf(str, "erode_%d.bmp", erodeCnt++);
            digitalToAnalog(digi_buffer_0, output_image);
            write_bitmap(output_image, str);
            nextState = DETECT_CELLS;
            break;

        case MARK_POINTS:
            //addMarkersToAnalogImage(input_image, points, pointIndex);
            addMarkersToAnalogImage(input_image, &points_head);
            nextState = EXIT;
            break;

        case DETECT_CELLS:
            t0 = clock();
            detectCells(digi_buffer_0, &points_head);
            t1 = clock();
            cpu_time_used = ((double)(t1 - t0)) / CLOCKS_PER_SEC;
            //printf("Detect time: %f s\n",cpu_time_used );
            nextState = ERODE_IMAGE;
            break;

        case EXIT:
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Total time: %f s\n", cpu_time_used);
            printPoints(&points_head);
            write_bitmap(input_image, argv[2]);

            run = FALSE;
            break;

        default:
            error("state machine error - undefined case");
            run = FALSE;
            break;
        }
    }
    return 0;
}
