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

#define PRINTTAB printf("    ");

#define PRINTCELL(i,j) {\
  if(matrix[i][j] == 0)\
    printf(". ");\
  else\
    printf("x ");\
  }

#define PRINTBLANKLINE printf("\n");


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

#endif /*_GOL_HEADER_*/
