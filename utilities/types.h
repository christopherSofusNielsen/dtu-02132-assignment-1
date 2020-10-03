#ifndef TYPES_H
#define TYPES_H

#define UCHAR unsigned char

#define BOOL unsigned char
#define TRUE 1
#define FALSE 0

typedef enum
{
    NEXT_BLACK,
    BLACK,
    WHITE
} PIXEL_STATE;

typedef struct
{
    int x;
    int y;
} POINT;

#endif