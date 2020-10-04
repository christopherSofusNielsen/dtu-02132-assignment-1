#include "filterCells.h"

void comparePoint(node_t **point);
UCHAR comparePointToCircularBounds(int x0, int y0, int x, int y);

void filterPoints(node_t **points_head)
{
    node_t *tmp = *points_head;

    //loop through all points to the tail of the list
    while (tmp != NULL)
    {
        comparePoint(&tmp);
        tmp = tmp->next;
    }
}

void comparePoint(node_t **point)
{

    //calculate bounds
    int x_min, x_max, y_min, y_max, x0, y0, x_sum = 0, y_sum = 0, nOverlaps = 0;
    x0 = (*point)->x;
    y0 = (*point)->y;

    x_min = (x0 - RADIUS < 0) ? 0 : x0 - RADIUS;
    x_max = (x0 + RADIUS > BMP_WIDTH_EDGE) ? BMP_WIDTH_EDGE : x0 + RADIUS;
    y_min = (y0 - RADIUS < 0) ? 0 : y0 - RADIUS;
    y_max = (y0 + RADIUS > BMP_HEIGTH_EDGE) ? BMP_HEIGTH_EDGE : y0 + RADIUS;

    //Compare to the rest of the points
    node_t *prev = *point;
    node_t *tmp = (*point)->next;

    //compare to all points after this point in the list
    while (tmp != NULL)
    {
        int x = tmp->x;
        int y = tmp->y;

        //Will stop checking conditions first time one is false
        if (x_min <= x && x <= x_max && y_min <= y && y <= y_max && comparePointToCircularBounds(x0, y0, x, y) != 0)
        {

            nOverlaps++;
            x_sum += x;
            y_sum += y;

            //remove point from the list
            prev->next = tmp->next;
            free(tmp);
            tmp = prev->next;
        }
        else
        {
            //go to next point
            prev = prev->next;
            tmp = tmp->next;
        }
    }

    //Calculate the avrage for x & y the removed points and set the "orignal" point to that.
    if (nOverlaps > 0)
    {
        nOverlaps++;
        x_sum += x0;
        y_sum += y0;

        int x_new = x_sum / nOverlaps;
        int y_new = y_sum / nOverlaps;

        (*point)->x = x_new;
        (*point)->y = y_new;
    }
}

UCHAR comparePointToCircularBounds(int x0, int y0, int x, int y)
{
    //calc distance with Pythagoras
    double r = sqrt(pow((x0 - x), 2) + pow((y0 - y), 2));
    return r <= (double)RADIUS;
    ;
}
