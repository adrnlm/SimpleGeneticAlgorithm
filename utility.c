/******************************************************************************
** Student name: 	Adrian Lim Song En
** Student number: 	s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "utility.h"

void * safeMalloc(size_t size)
{
    void *p = malloc(size);

    if (p == NULL)
    {
        perror(NULL);
        exit(EXIT_FAILURE);
    }
    return p;
}
