#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "utilities/parameters.h"
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

//Only for debug
UCHAR output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
UCHAR erodeCnt = 0;

UCHAR binary_image_0[BMP_WIDTH][BMP_HEIGTH];
UCHAR binary_image_1[BMP_WIDTH][BMP_HEIGTH];

UCHAR (*digi_buffer_0)
[BMP_HEIGTH] = binary_image_0;
UCHAR (*digi_buffer_1)
[BMP_HEIGTH] = binary_image_1;

//Swap the pointers to the BW images
void swap(UCHAR (**a)[BMP_WIDTH], UCHAR (**b)[BMP_WIDTH])
{
    UCHAR(*temp)
    [BMP_WIDTH] = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char *argv[])
{

    STATES state, nextState = INIT;
    BOOL run = TRUE;
    node_t *points_head = NULL;
    unsigned long int whitePixels = 0;

    //Debug - eroded images
    char str[30] = {'\0'};

    //Time control
    INIT_STATE_TIME;
    clock_t start, end;
    double cpu_time_used;

    while (run)
    {
        state = nextState;
        switch (state)
        {
        case INIT:
            LOG("Program start!\n");
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
            read_bitmap(argv[1], input_image);
            start = clock();
            nextState = RGB_TO_GRAY;
            break;

        case RGB_TO_GRAY:
            START_TIME;
            rgbToGrayscale(input_image, digi_buffer_0);
            STOP_TIME("\nRGB to grayscale time: %f s\n\n");
            nextState = GRAY_TO_BW;
            break;

        case GRAY_TO_BW:
            START_TIME;
            grayscaleToBlackWhiteOtsu(digi_buffer_0);
            STOP_TIME("Grayscale to black/white time: %f s\n\n");
            nextState = ERODE_IMAGE;
            break;

        case ERODE_IMAGE:
            START_TIME;
            //count number of white pixels, to know when the image is 100% eroded
            whitePixels = 0;
            whitePixels = erodeImage(digi_buffer_0, digi_buffer_1);
            swap(&digi_buffer_0, &digi_buffer_1);
            STOP_TIME("Erode time: %f s\n");
            nextState = CHECK_ERODED_IMAGE;
            break;

        case CHECK_ERODED_IMAGE:
            if (whitePixels == 0)
            {
                nextState = FITLER_POINTS;
            }
            else
            {
                nextState = DETECT_CELLS;
            }
            break;

        case DETECT_CELLS:
            START_TIME;
            detectCells(digi_buffer_0, &points_head);
            STOP_TIME("Detect time: %f s\n\n");
            nextState = ERODE_IMAGE;
            break;

        case FITLER_POINTS:
            START_TIME;
            filterPoints(&points_head);
            STOP_TIME("\nFilter points: %f s\n\n");
            nextState = MARK_POINTS;
            break;

        case MARK_POINTS:
            START_TIME;
            addMarkersToAnalogImage(input_image, &points_head);
            STOP_TIME("Mark points: %f s\n\n");
            nextState = EXIT;
            break;

        //Only for debugging
        case PRINT_ERODE_IMAGE:
            sprintf(str, "erode_%d.bmp", erodeCnt++);
            digitalToAnalog(digi_buffer_0, output_image);
            write_bitmap(output_image, str);
            nextState = DETECT_CELLS;
            break;

        case EXIT:
            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

            if (argc >= 4 && strcmp(argv[3], "ls") == 0)
            {
                printPoints(&points_head);
            }
            else
            {
                printResult(&points_head);
            }
            printf("\nTotal time: %f s\n", cpu_time_used);
            write_bitmap(input_image, argv[2]);

            run = FALSE;
            break;

        default:
            LOG("state machine error - undefined case\n");
            run = FALSE;
            break;
        }
    }
    return 0;
}
