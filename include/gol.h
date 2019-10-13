/**
 * @file gol.h
 * @author Mrukant Popat
 * @brief Game Of Life header file
 */

#ifndef _GOL_HEADER_
#define _GOL_HEADER_

#include <stdio.h>
#include <time.h>
#include <stdlib.h> /* srand, rand */

#define ROW 8
#define COL 8
#define NEIGH_MATRIX_ROW 3
#define NEIGH_MATRIX_COL 3


#define PRINTTAB printf("    ");

#define PRINTCELL(i,j) {\
  if(matrix[i][j] == 0)\
    printf(". ");\
  else\
    printf("x ");\
  }

#define PRINTBLANKLINE printf("\n");



#define LEFTBOUND(x) (x == -1)
#define TOPBOUND(x) (x == -1)
#define RIGHTBOUND(x) (x >= COL)
#define BOTTOMBOUND(x) (x >= ROW)
  


/**
@brief Program init 
*/
void init();

/**
@brief Initialize matrix with random values 
*/
void init_matrix();

/**
@brief Print the whole matrix 
*/
void print_matrix();

/**
@brief starts the main program loop
*/
void start_gol();

/**
@brief Readies matrix to be printed in next generation
*/
void get_nextgen_matrix();

/**
@brief Calculates the cell value for next gen based on GOL neighbor values
*/
int get_nextgen_cell(int i, int j);

#endif /*_GOL_HEADER_*/
