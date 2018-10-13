/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "invector.h"
#include "drive.h"

void invector_init(InVTable *invt) {
	/* TO DO */
  invt->tot = 0;
  invt->width = 0;
}

int read_line(char *line, int numOfPar, InVector array, int lineNumber, char
*geneType)
{
  char *current;
  int counter, maxSize, points;
  /*Check if the initial spelling is correct*/
  current = strtok(line, INV_DELIM1);
  if (strcmp(current, INV_LABEL) != 0){
    printf("[WRONG FORMAT]\n");
    return -1;
  }
  /*Check if the line number is in correct order*/
  current = strtok(NULL, INV_DELIM2);
  points = stringToInt(current);
  if (points != lineNumber){
    printf("[WRONG LINE NUMBER]\n");
    return -1;
  }
  /*Checks what size to give depending on the gene type*/
  if (strcmp(geneType,CMD_ARG_MINFN)==0){
    maxSize = numOfPar+1;
  }
  else{
    maxSize = 2;
  }
  /*Count all the points in the input vector and store them in the array*/
  for (counter=0; counter<maxSize; counter++){
    current = strtok(NULL, INV_DELIM3);
    if(strcmp(current, "\n") ==0 || strcmp(current, "\0") ==0){
      printf("[COUNT MISMATCH: %d] \n", numOfPar );
      return -1;
    }
    points = stringToInt(current);
    if (points == -1){
      printf("[INVALID PARAMETERS]\n" );
      return -1;
    }
    array[counter] = points;
  }
  /*Check the last point if the count is correct*/
  current = strtok(NULL, INV_DELIM3);
  if(strcmp(current, "\n") !=0 ){
    if(strcmp(current, "\0") !=0){
      printf("[COUNT MISMATCH: %d] \n", numOfPar );
      return -1;
    }
  }
  return lineNumber;
}
