/**
 * @file gol.c
 * @author Mrukant Popat
 * @brief Game Of Life stand-alone implementation file
 */

#include "gol.h"


int matrix[ROW][COL]={0};
int temp_matrix[ROW][COL]={0};
mat_ptr2d matrix_ptr;
mat_ptr2d temp_matrix_ptr;
  

void init_matrix(){
  srand(time(NULL));
  int i,j; /* loop variable */
  matrix_ptr = matrix;
  temp_matrix_ptr = temp_matrix;

  for(i=0 ; i<ROW ; i++){
    for(j=0 ; j<COL ; j++){
      matrix_ptr[i][j] = rand() % 2;
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


int apply_gol_rules(int on_neigh, bool mystate){
  /* 1) Any live cell with fewer than two live neighbours dies, as if by underpopulation.
     2) Any live cell with two or three live neighbours lives on to the next generation.
     3) Any live cell with more than three live neighbours dies, as if by overpopulation.
     4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction. */

  if(mystate){
    if(on_neigh < 2)
      return OFF;
    else if((on_neigh == 2) || (on_neigh == 3))
      return ON;
    else if(on_neigh >3)
      return OFF;
  }
  else{
    if(on_neigh == 3)
      return ON;
  }

  return OFF;    
}



int get_nextgen_cell(int i, int j, bool mystate){
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

      if(matrix_ptr[i_neigh][j_neigh])
        on_neighbors++;
    }   
  }

  //return 0;

  return apply_gol_rules(on_neighbors, mystate);
}


void swap_matrix(mat_ptr2d *matrix, mat_ptr2d *temp_matrix){
  mat_ptr2d temp = *matrix;
  *matrix = *temp_matrix;
  *temp_matrix = temp;
}


void get_nextgen_matrix(){
  int i = 0, j = 0;
  
  bool mystate;
  for(i=0 ; i<ROW; i++){
    for(j=0; j<COL; j++){
      mystate = (matrix_ptr[i][j] == ON)? true : false;
      temp_matrix_ptr[i][j] = get_nextgen_cell(i,j, mystate);
    }
  }

  swap_matrix(&matrix_ptr, &temp_matrix_ptr);
}

void start_gol(){
  int i = 0;

  for(i=0 ; i<4 ; i++){
    get_nextgen_matrix();
    print_matrix();
  }
}


int main(){
  init();
  start_gol();  
}
