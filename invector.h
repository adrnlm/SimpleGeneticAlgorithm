/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#ifndef INVECTOR_H
#define INVECTOR_H

#include "utility.h"

/* Maximum width of an input vector */
#define INVT_WIDTH 5
/* Maximum number of input vectors that can be stored */
#define INVT_MAX 50

/* Delimitors for a line of data from an input vector data file */
#define INV_LABEL "InputVector"
#define INV_DELIM1 ":"
#define INV_DELIM2 "("
#define INV_DELIM3 ",)"

#define DECIMAL 10

#define EXTRA_SPACES 2

#define INV_LEN 80

typedef int InVector[INVT_WIDTH];

/* The table for storing input vectors */
typedef struct invector_table
{
    /* Each row of the table will store one input vector
     * For example: input of
     * 		InputVector:0(1,3,4,2,40)
     * would store 1,3,4,2,40 in the first 5 indexes of the InVector at
     * table[0]
     * */
    InVector table[INVT_MAX];
    /* the top of the table - the next location that we can add a
     * input vector */
    int tot;
    /* the width of the input vector */
    int width;
} InVTable;

/* Initialise the InVTable to a safe state */
void invector_init(InVTable *invt);

/* TO DO - other functions as appropriate */

#endif
