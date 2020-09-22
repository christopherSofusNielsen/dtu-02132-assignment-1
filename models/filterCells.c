#include "filterCells.h"

POINT combinePoints(POINT pnts[POINTS_LENGTH], int nPoints, int skipPoints[MAX_SKIP_POINTS], int *nSkipPnts, int index);
BOOL hasValus(int skipPoints[MAX_SKIP_POINTS], int length, int val);

void removeOverlappingCells(POINT pnts[POINTS_LENGTH], int *nPoints)
{
    POINT *filteredPnts = malloc(sizeof(POINT) * POINTS_LENGTH);
    int nFilteredPoints = 0;
    int nSkipPnts = 0;
    int skipPnts[MAX_SKIP_POINTS];

    for (int i = 0; i < (*nPoints); i++)
    {
        if (hasValus(skipPnts, nSkipPnts, i))
        {
            //printf("Skipped index %d\n", i);
            continue;
        }

        filteredPnts[i] = combinePoints(pnts, (*nPoints), skipPnts, &nSkipPnts, i);
        nFilteredPoints++;
    }

    (*nPoints) = nFilteredPoints;
    memcpy(pnts, filteredPnts, sizeof(POINT) * POINTS_LENGTH);
    free(filteredPnts);
}

POINT combinePoints(POINT pnts[POINTS_LENGTH], int nPoints, int skipPoints[MAX_SKIP_POINTS], int *nSkipPnts, int index)
{

    unsigned int xMin, xMax, yMin, yMax, xSum, ySum, cnt;
    xSum = pnts[index].x;
    ySum = pnts[index].y;
    cnt = 1;

    xMin = (pnts[index].x - MAX_OVERLAP_RADIUS < 0) ? 0 : pnts[index].x - MAX_OVERLAP_RADIUS;
    xMax = (pnts[index].x + MAX_OVERLAP_RADIUS > BMP_WIDTH - 1) ? BMP_WIDTH - 1 : pnts[index].x + MAX_OVERLAP_RADIUS;
    yMin = (pnts[index].y - MAX_OVERLAP_RADIUS < 0) ? 0 : pnts[index].y - MAX_OVERLAP_RADIUS;
    yMax = (pnts[index].y + MAX_OVERLAP_RADIUS > BMP_HEIGTH - 1) ? BMP_HEIGTH - 1 : pnts[index].y + MAX_OVERLAP_RADIUS;

    printf("xMin %d, xMax %d, yMin %d, yMax %d\n", xMin, xMax, yMin, yMax);

    for (int i = 0; i < nPoints; i++)
    {
        if (i == index)
        {
            continue;
        }

        int x = pnts[i].x, y = pnts[i].y;

        if (x >= xMin && x <= xMax && y >= yMin && y <= yMax)
        {
            //xSum += x;
            //ySum += y;
            skipPoints[(*nSkipPnts)++] = i;
            cnt++;
            //printf("Combined %d with %d\n", index, i);
        }
    }

    //POINT p = {.x = xSum / cnt, .y = ySum / cnt};
    POINT p = {.x = xSum, .y = ySum};
    return p;
}

BOOL hasValus(int skipPoints[MAX_SKIP_POINTS], int length, int val)
{
    for (int i = 0; i < length; i++)
    {
        if (skipPoints[i] == val)
        {
            return TRUE;
        }
    }
    return FALSE;
}