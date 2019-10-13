/**
 * @file gol.c
 * @author Mrukant Popat
 * @brief Game Of Life stand-alone implementation file
 */

#include "gol.h"


int matrix[ROW][COL]={0};
int temp_matrix[ROW][COL]={0};

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


int get_nextgen_cell(int i, int j){
  int off_neighbors = 0;
  int on_neighbors = 0;
  
  int i_neigh = 0 , j_neigh = 0; /* neighbor indexes */
  int i_neigh_start = i-1;
  int j_neigh_start = j-1;
  
  for(i_neigh=i_neigh_start ; i_neigh<i_neigh_start+3 ; i_neigh++){
    for(j_neigh=j_neigh_start ; j_neigh<j_neigh_start+3 ; j_neigh++){
      if(LEFTBOUND(j_neigh) || TOPBOUND(i_neigh) || RIGHTBOUND(j_neigh) || BOTTOMBOUND(i_neigh)) /* if index out of bounds */
        continue;

      if((i_neigh == i) && (j_neigh == j)) /* discard current cell */
        continue;

      if(matrix[i_neigh][j_neigh])
        on_neighbors++;
      else
        off_neighbors++;

    }   
  }

  return 0;
}

void get_nextgen_matrix(){
  int i = 0, j = 0;

  for(i=0 ; i<ROW; i++){
    for(j=0; j<COL; j++){
      temp_matrix[i][j] = get_nextgen_cell(i,j);
    }
  }
  
}

void start_gol(){
  int i = 0;

  for(i=0 ; i<4 ; i++){
    get_nextgen_matrix();
    print_matrix();
  }
}

int main(){
  /* 1) Init a random sequence and populate first matrix     
     2) check neighors and change individual values
     3) print new sequence
     4) repeat from 3)  */


  /*1) Init a random sequence and populate first matrix*/
  init();

  start_gol();

  
}
