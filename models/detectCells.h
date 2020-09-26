#if !defined(DETECT_CELLS_H)
#define DETECT_CELLS_H
#include "../utilities/cbmp.h"
#include "../utilities/types.h"
#include "../utilities/parameters.h"
#include "../utilities/list.h"

void detectCells(UCHAR image[BMP_WIDTH][BMP_HEIGTH], node_t **points_head);

#endif // DETECT_CELLS_H
