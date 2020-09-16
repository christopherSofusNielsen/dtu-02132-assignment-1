#if !defined(DETECT_CELLS_H)
#define DETECT_CELLS_H
#include "../utilities/cbmp.h"
#include "../utilities/types.h"
#include "../utilities/parameters.h"


void detectCells(UCHAR image[BMP_WIDTH][BMP_HEIGTH], POINT points[POINTS_LENGTH], int *pointIndex);


#endif // DETECT_CELLS_H
