/**
 * @file gol.c
 * @author Mrukant Popat
 * @brief Game Of Life stand-alone implementation file
 */

#include "gol.h"


int matrix[ROW][COL]={0};

void init_matrix(){
  srand(time(NULL));
  int i,j; /* loop variable */

  for(i=0 ; i<ROW ; i++){
    for(j=0 ; j<COL ; j++){
      matrix[i][j] = rand() % 2;
    }
  }
}


void print_matrix(){
  int i,j;

  PRINTBLANKLINE;
  
  for(i=0 ; i<ROW ; i++){
    PRINTTAB;
    for(j=0 ; j<COL ; j++){
      PRINTCELL(i,j);
    }
    PRINTBLANKLINE;
  }

  PRINTBLANKLINE;
}


void init(){
  init_matrix();
  printf("\n");
  print_matrix();
}



int main(){
  /* 1) Init a random sequence and populate first matrix
     2) print this randon sequence
     3) check neighors and change individual values
     4) print new sequence
     5) repeat from 3)  */


  /*1) Init a random sequence and populate first matrix*/
  init();
  
}
