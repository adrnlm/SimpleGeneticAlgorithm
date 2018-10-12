/******************************************************************************
** Student name: Adrian Lim Song En
** Student number: s3710625
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "invector.h"

void invector_init(InVTable *invt) {
	/* TO DO */
  invt->tot = 0;
  invt->width = 0;
}

int read_line(char *line, int numOfPar, InVector array, int lineNumber){
  char *current;
  int counter , points;

  current = strtok(line, ":");
  if (strcmp(current, "InputVector") != 0){
    printf("[WRONG FORMAT]\n");
    exit(0);
  }
  current = strtok(NULL, "(");
  points = stringToInt(current);
  if (points != lineNumber){
    printf("[WRONG LINE NUMBER]\n");
    exit(0);
  }

  for (counter=0; counter<=numOfPar; counter++){
    current = strtok(NULL, ",)");
    if(strcmp(current, "\n") ==0 || strcmp(current, "\0") ==0){
      printf("\n[COUNT MISMATCH: %d] \n", numOfPar );
      exit(0);
    }
    points = stringToInt(current);
    if (points == -1){
      printf("[INVALID PARAMETERS]\n" );
      exit(0);
    }
    array[counter] = points;
  }
  current = strtok(NULL, ",)");
  if(strcmp(current, "\n") !=0 ){
    if(strcmp(current, "\0") !=0){
      printf("\n[COUNT MISMATCH: %d] \n", numOfPar );
      exit(0);
    }
  }
  return lineNumber;
}
