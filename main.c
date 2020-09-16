#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utilities/cbmp.h"
#include "utilities/states_enum.h"
#include "utilities/types.h"
#include "utilities/logger.h"

#include "models/imageConverter.h"
#include "models/erode.h"
#include "models/detectCells.h"


//variabels
UCHAR input_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
UCHAR output_image[BMP_WIDTH][BMP_HEIGTH][BMP_CHANNELS];
UCHAR digital_image[BMP_WIDTH][BMP_HEIGTH];
UCHAR temp_digital_image[BMP_WIDTH][BMP_HEIGTH];
unsigned long int whitePixels=0;
int pointIndex=0; 
POINT points[POINTS_LENGTH];

int main(int argc, char *argv[])
{
    //State vars
    STATES state, nextState=INIT;
    BOOL run=TRUE;

    while (run)
    {
        state=nextState;
        switch (state)
        {
        case INIT:
            info("init state");
            if (argc != 3)
            {
                fprintf(stderr, "Usage: %s <output file path> <output file path>\n", argv[0]);
                nextState=EXIT;
            }else{
                nextState=LOAD_FILE;
            }
            break;

        case LOAD_FILE:
            info("load file state");
            read_bitmap(argv[1], input_image);

            nextState=RGB_TO_GRAY;
            break;

        case RGB_TO_GRAY:
            info("rgb to gray scale state");
            rgbToGrayscale(input_image, digital_image);

            nextState=GRAY_TO_BW;
            break;

        case GRAY_TO_BW:
            info("gray to bw state");
            grayscaleToBlackWhite(digital_image);
            nextState=ERODE_IMAGE;
            break;

        case ERODE_IMAGE:
            whitePixels=0;
            whitePixels=erodeImage(digital_image, temp_digital_image);
            printf("White pixels: %d\n", whitePixels);
            memcpy(digital_image, temp_digital_image, sizeof(temp_digital_image));
            nextState=INIT_ANALYSIS;
            break;

        case INIT_ANALYSIS:
            if(whitePixels==0){
                nextState=MARK_POINTS;
            }else{
                nextState=DETECT_CELLS;
            }
            break;

        case MARK_POINTS:
            printPoints(points, pointIndex);
            addMarkersToAnalogImage(input_image, points, pointIndex);
            nextState=EXIT;
            break;

        case DETECT_CELLS:
            detectCells(digital_image, points, &pointIndex);
            nextState=ERODE_IMAGE;
            break;

        case EXIT:
            info("exit state");
            //digitalToAnalog(digital_image, output_image);
            write_bitmap(input_image, argv[2]);

            run=FALSE;
            break;

        default:
            error("state machine error - undefined case");
            run=FALSE;
            break;
        }
    }
    return 0;
}
