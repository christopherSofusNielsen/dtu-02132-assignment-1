

#if !defined(PARAMETERS_H)
#define PARAMETERS_H

#define DEBUG 0      //enable debug messages
#define STATE_TIME 1 //enable time analysis

//basic gray to bw
#define GRAYSCALE_THRESHOLD 100  //Static threshold - also used as fallback threshold
#define OTSU_MIN  90             //set to zero for disabling otsu threshold
#define OTSU_MAX 150             //set to zero for disabling otsu threshold

//x-0 (no otsu) best for easy
//90-150 best for medium
//90-150 best for medium

//Detect box size
#define CELL_DETECT_BOX_SIZE 8

//Filter overlap
#define RADIUS 16

//Mark cells
#define CROSS_R_SIZE 8

#endif // PARAMETERS_H
