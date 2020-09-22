#if !defined(FILTER_CELLS_H)
#define FILTER_CELLS_H

#include "../utilities/types.h"
#include "../utilities/parameters.h"
#include "../utilities/cbmp.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_SKIP_POINTS 400

void removeOverlappingCells(POINT pnts[POINTS_LENGTH], int *nPoints);

#endif // FILTER_CELLS_H
