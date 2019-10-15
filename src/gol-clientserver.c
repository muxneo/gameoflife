/**
 * @file gol-clientserver.c
 * @author Mrukant Popat
 * @brief Game Of Life server implementation file
 */

#include "gol-clientserver.h"


void print_help(){
  printf("\n");
  printf("Client usage:\n");
  printf(" h  - prints this help\n");
  printf(" 4D - flips (kills or ressurects) cell at row 4 column D\n");
  printf(" .  - retrieves and prints current state of the board\n");
  printf(" o  - Init board with TOAD\n");
  printf(" n  - Init board with BEACON\n");
  printf(" i  - Init board with BLINKER\n");
  printf(" r  - Init board with RANDOM\n");
  printf(" s  - Executes single-setp\n");
  printf(" g  - Go run server continuously executing generation steps\n");
  printf(" t  - Stop\n");
  printf(" q  - Quit and disconnect from server(Leaving it running)\n");
  printf(" k  - Quit and kill server\n\n");
  //  printf(" Client is connected to port %d",port);
  printf(" %d>",gen);
}

int connect_to_server(){
  int client_sock_fd;
  struct sockaddr_un clntsockinfo;

  /* create socket */
  client_sock_fd =  socket(PF_LOCAL,SOCK_STREAM,0);

  clntsockinfo.sun_family = PF_LOCAL;
  strcpy(clntsockinfo.sun_path,GOLSOCKET);
  connect(client_sock_fd, (struct sockaddr*) &clntsockinfo, SUN_LEN(&clntsockinfo));

  return client_sock_fd;
}

void* client_matrix_thread(void* thread_args){
  //printf("\n CLIENT MATRIX THREAD\n");
  while(true){
   
  }
}

void send_command_srv(int client_socket, const char* command){
  int comm_len = strlen(command) + 1;
  write(client_socket, &comm_len, sizeof(comm_len)); /* send length */
  write(client_socket, &command, comm_len);
}

void start_client(){
  /*
   - create matrix print thread
   - main thread - create socket and connect to server
   - main thread - create a loop to accept user input and send to server
   - matrix thread - wait for data from server and print
   */

  char command[COMMANDSIZE];
  int client_sockfd;
  
  pthread_t matrixcthread_id;
  pthread_create(&matrixcthread_id, NULL, &client_matrix_thread, NULL);

  client_sockfd = connect_to_server();
  
  print_help();
  
  while(true){
    scanf("%s",command);
    send_command_srv(client_sockfd, command);
  }
  
}






void* server_matrix_thread(void* thread_args){
  printf("\n SERVER MATRIX THREAD\n");

  while(true){
    
  }
}


int connect_to_client(){
  int server_sock_fd;
  int client_sockfd_accept;
  struct sockaddr_un srvsockinfo;
  struct sockaddr_un clntsockinfo_srv;
  socklen_t clntsockinfosrv_len;

  /* create socket */
  server_sock_fd =  socket(PF_LOCAL,SOCK_STREAM,0);

  srvsockinfo.sun_family = PF_LOCAL;
  strcpy(srvsockinfo.sun_path,GOLSOCKET);
  bind(server_sock_fd, (struct sockaddr*) &srvsockinfo, SUN_LEN(&srvsockinfo));
  listen(server_sock_fd,1);
  
  client_sockfd_accept = accept(server_sock_fd, (struct sockaddr*) &clntsockinfo_srv, &clntsockinfosrv_len);

  return client_sockfd_accept;
}


void read_client_command(int client_sockfd_srv, char* command){
  int len = 0;
  char* comm;
  
  while(true){
    
    if(read(client_sockfd_srv, &len, sizeof(len)) == 0){
      printf("read len ");
      return;
    }
    if(len !=0) printf("len = %d\n",len);
    comm = (char*) malloc(len);
    
    read(client_sockfd_srv, comm, len);
  }
  printf("\n SERVER received %s\n", comm);
  free(comm);
}


void start_server(){
  printf("\n SERVER \n");
  int client_sockfd_srv;
  char command[COMMANDSIZE];
  

  /*
    - create matrix calc thread
    - main thread - default shared data-struct create socket, bind, listen, read
    - matrix thread - read shared data-struct, change shared ds, calc, write to socket
   */

  pthread_t matrixsthread_id;
  pthread_create(&matrixsthread_id, NULL, &server_matrix_thread, NULL);

  client_sockfd_srv = connect_to_client();
  
  //while(true){
    read_client_command(client_sockfd_srv, command);
    
    //}
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
