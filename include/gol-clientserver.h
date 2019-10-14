/**
 * @file gol-clientserver.h
 * @author Mrukant Popat
 * @brief Game Of Life client-server header file
 */

#ifndef _GOL_SERVER_HEADER_
#define _GOL_SERVER_HEADER_

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h> /* bool datatype */


/**
@brief starts client logic
*/
void start_client();

/**
@brief server thread to calculate matrix
*/
void* client_matrix_thread(void* thread_args);


/**
@brief starts server logic
*/
void start_server();

/**
@brief server thread to calculate matrix
*/
void* server_matrix_thread(void* thread_args);




#endif /*_GOL_SERVER_HEADER_*/
