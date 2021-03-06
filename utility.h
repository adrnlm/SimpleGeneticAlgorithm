/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum boolean{
    FALSE = 0,
    TRUE
} Boolean;

/*Allocate memory*/
void *safeMalloc();

/*Convert an array of characters to integers*/
int stringToInt();

/*Produce a random percentage*/
int randomPercentage();

#endif
