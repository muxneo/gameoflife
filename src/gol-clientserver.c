/**
 * @file gol-server.c
 * @author Mrukant Popat
 * @brief Game Of Life server implementation file
 */

#include "gol-clientserver.h"



void* client_matrix_thread(void* thread_args){
  printf("\n CLIENT MATRIX THREAD\n");

  while(true){
    
  }
}

void start_client(){
  printf("\n CLIENT \n");

  /*
   - create matrix print thread
   - main thread - create socket and connect to server
   - main thread - create a loop to accept user input and send to server
   - matrix thread - wait for data from server and print
   */

  pthread_t matrixcthread_id;
  pthread_create(&matrixcthread_id, NULL, &client_matrix_thread, NULL);

  while(true){
  }
  
}




void* server_matrix_thread(void* thread_args){
  printf("\n SERVER MATRIX THREAD\n");

  while(true){
    
  }
}

void start_server(){
  printf("\n SERVER \n");

  /*
    - create matrix calc thread
    - main thread - default shared data-struct create socket, bind, listen, read
    - matrix thread - read shared data-struct, change shared ds, calc, write to socket
   */

  pthread_t matrixsthread_id;
  pthread_create(&matrixsthread_id, NULL, &server_matrix_thread, NULL);

  while(true){
  }
}




int main(int argc, char* argv[]){
  /*
   - create client or server based on args
    1) Create 1 thread for calculating matrix.
  2) Start a socket server in main thread after creating matrix calculating thread and set comand variable to NOP
  3) Wait for connection from client
  4) main server thread set global command variable to command received from client
  5) matrix thread in infinite loop 
  5.1) Check command - skip task for NOP
  5.2) Do work for other non-NOP commands (set to NOP the global command variable if required)
  */

  (void) argc; /* shuts down compiler warning about unused argc */
  if(strstr(argv[0],"gol-client"))
    start_client();
  else
    start_server();
}
