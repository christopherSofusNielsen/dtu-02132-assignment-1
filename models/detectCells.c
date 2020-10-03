#include "detectCells.h"

#include <stdio.h>

//BOOL searchForCell(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);
BOOL searchBox(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih);
BOOL cheackRowForWhite(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int row, int colStart, int colEnd);
BOOL cheackColForWhite(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int col, int rowStart, int rowEnd);
void makeBlack(UCHAR image[BMP_WIDTH][BMP_HEIGTH], UCHAR radius, int iwCenter, int ihCenter);

void detectCells(UCHAR image[BMP_WIDTH][BMP_HEIGTH], node_t **points_head)
{
    node_t *tmp;
    for (int iw = 0; iw < BMP_WIDTH; iw++)
    {
        for (int ih = 0; ih < BMP_HEIGTH; ih++)
        {
            if (image[iw][ih] > 0)
            {
                BOOL haveCell = searchBox(image, iw, ih);
                if (haveCell == TRUE)
                {
                    //if cell detected then add to linked list
                    tmp = create_new_node(iw, ih);
                    insert_at_head(points_head, tmp);
                }
            }
        }
    }
}

BOOL searchBox(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int iw, int ih)
{
    int radius = CELL_DETECT_BOX_SIZE;
    //TOP
    if (cheackRowForWhite(image, ih - radius, iw - radius, iw + radius))
    {
        return FALSE;
    }
    //Bottom
    if (cheackRowForWhite(image, ih + radius, iw - radius, iw + radius))
    {
        return FALSE;
    }
    //LEFT
    if (cheackColForWhite(image, iw - radius, ih - radius, ih + radius))
    {
        return FALSE;
    }
    //RIGHT
    if (cheackColForWhite(image, iw + radius, ih - radius, ih + radius))
    {
        return FALSE;
    }

    makeBlack(image, radius, iw, ih);
    return TRUE;
}

void makeBlack(UCHAR image[BMP_WIDTH][BMP_HEIGTH], UCHAR radius, int iwCenter, int ihCenter)
{
    int colStart = (iwCenter - radius < 0) ? 0 : iwCenter - radius;
    int colEnd = (iwCenter + radius >= BMP_WIDTH) ? BMP_WIDTH - 1 : iwCenter + radius;

    for (int iw = colStart; iw < colEnd; iw++)
    {

        int rowStart = (ihCenter - radius < 0) ? 0 : ihCenter - radius;
        int rowEnd = (ihCenter + radius >= BMP_HEIGTH) ? BMP_HEIGTH - 1 : ihCenter + radius;

        for (int ih = ihCenter - radius; ih < ihCenter + radius; ih++)
        {
            image[iw][ih] = 0;
        }
    }
}

//no whites if false
BOOL cheackRowForWhite(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int row, int colStart, int colEnd)
{
    if (row < 0 || row >= BMP_HEIGTH)
    {
        //row out of matrix
        return FALSE;
    }
    colStart = (colStart < 0) ? 0 : colStart;
    colEnd = (colEnd >= BMP_WIDTH) ? BMP_WIDTH - 1 : colEnd;

    for (int iw = colStart; iw <= colEnd; iw++)
    {
        if (image[iw][row] > 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL cheackColForWhite(UCHAR image[BMP_WIDTH][BMP_HEIGTH], int col, int rowStart, int rowEnd)
{
    if (col < 0 || col >= BMP_WIDTH)
    {
        //row out of matrix
        return FALSE;
    }

    rowStart = (rowStart < 0) ? 0 : rowStart;
    rowEnd = (rowEnd >= BMP_HEIGTH) ? BMP_HEIGTH - 1 : rowEnd;

    for (int ih = rowStart; ih <= rowEnd; ih++)
    {
        if (image[col][ih] > 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}
