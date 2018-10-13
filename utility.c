/******************************************************************************
** Student name: 	Adrian Lim Song En
** Student number: 	s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "utility.h"

void * safeMalloc(size_t size)
{
  void *p = malloc(size);

  if (p == NULL){
    perror(NULL);
    exit(EXIT_FAILURE);
  }
  return p;
}

int stringToInt(char *string)
{
  int integer;
  char *endPtr = NULL;
  integer = strtol(string, &endPtr, 10);
  if ( string == endPtr || *endPtr != '\0'){
    if(string == NULL){
      perror("Error: invector string invalid");
      exit(EXIT_FAILURE);
    }
    return -1;
  }
  return integer;
}

int randomPercentage()
{
  return (rand() % 100 + 1);
}
