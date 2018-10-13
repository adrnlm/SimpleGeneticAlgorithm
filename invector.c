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

int read_line(char *line, int numOfPar, InVector array, int lineNumber, char *geneType){
  char *current;
  int counter, maxSize, points;

  current = strtok(line, ":");
  if (strcmp(current, "InputVector") != 0){
    printf("[WRONG FORMAT]\n");
    return -1;
  }

  current = strtok(NULL, "(");
  points = stringToInt(current);
  if (points != lineNumber){
    printf("[WRONG LINE NUMBER]\n");
    return -1;
  }

  if (strcmp(geneType,CMD_ARG_MINFN)==0){
    maxSize = numOfPar+1;
  }
  else{
    maxSize = 2;
  }
  for (counter=0; counter<maxSize; counter++){
    current = strtok(NULL, ",)");
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

  current = strtok(NULL, ",)");
  if(strcmp(current, "\n") !=0 ){
    if(strcmp(current, "\0") !=0){
      printf("\n[COUNT MISMATCH: %d] \n", numOfPar );
      return -1;
    }
  }
  return lineNumber;
}
