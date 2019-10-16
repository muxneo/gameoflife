/**
 * @file gol.h
 * @author Mrukant Popat
 * @brief Game Of Life header file
 */

#ifndef _GOL_CLIENTSERVER_MATRIX_HEADER_
#define _GOL_CLIENTSERVER_MATRIX_HEADER_

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define ROW 8
#define COL 8
#define NEIGH_MATRIX_ROW 3
#define NEIGH_MATRIX_COL 3
#define ON 1
#define OFF 0


typedef int (*mat_ptr2d)[COL];

#define PRINTTAB printf("    ");

#define PRINTCELL(i,j,matrix) {                       \
  if(matrix[i][j] == OFF)\
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
@brief init_matrix Initialize matrix with random values 
*/
void init_matrix();

/**
@brief print_matrix_srv Print the whole matrix on server side 
*/
void print_matrix_srv();

/**
@brief Readies matrix to be printed in next generation
*/
void get_nextgen_matrix();

/**
@brief Calculates the cell value for next gen based on GOL neighbor values
*/
int get_nextgen_cell(int i, int j, bool mystate);

/**
@brief business logic / rules for GOL
*/
int apply_gol_rules(int on_neighbors, bool mystate);

/**
@brief Swapping matrix/arrays to avoid copy
*/
void swap_matrix(mat_ptr2d *matrix, mat_ptr2d *temp_matrix);


#endif /*_GOL_CLIENTSERVER_MATRIX_HEADER_*/

