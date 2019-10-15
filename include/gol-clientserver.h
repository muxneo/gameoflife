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
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h> /* read, write functions */
#include <stdlib.h> /* malloc */


#define GOLSOCKET "/tmp/golsocket"
#define COMMANDSIZE 20

/* Shared data between client threads - start */
int gen = 0;
/* Shared data with thread - end   */

/**
@brief send_command_srv sends command entered by user to server
*/
void send_command_srv(int client_socket, const char* command);

/**
@brief connect_to_server socket connection to initiate connection to server
*/
int connect_to_server();


/**
@brief print_help prints list of commands for user to use
*/
void print_help();

/**
@brief start_client starts client logic
*/
void start_client();

/**
@brief client_matrix_thread server thread to calculate matrix
*/
void* client_matrix_thread(void* thread_args);


/**
@brief start_server starts server logic
*/
void start_server();

/**
@brief server_matrix_thread server thread to calculate matrix
*/
void* server_matrix_thread(void* thread_args);

/**
@brief connect_to_client server-side socket connection
*/
int connect_to_client();


/**
@brief read_client_command read command sent by client
*/
void read_client_command(int client_sockfd_srv, char* command);

#endif /*_GOL_SERVER_HEADER_*/
