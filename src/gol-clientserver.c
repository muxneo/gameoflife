/**
 * @file gol-clientserver.c
 * @author Mrukant Popat
 * @brief Game Of Life server implementation file
 */

#include "gol-clientserver.h"
#include "gol-clientserver-matrix.h"

extern int matrix_srv[ROW][COL];


int toadmat[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,0,1,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
};


int beaconmat[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,1,1,0,0,0,0},
  {0,0,1,1,0,0,0,0},
  {0,0,0,0,1,1,0,0},
  {0,0,0,0,1,1,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
};


int blinkermat[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
};



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

void print_matrix_client(int** rcvd_matrix){
  int i,j;

  PRINTBLANKLINE;
  
  for(i=0 ; i<ROW ; i++){
    PRINTTAB;
    for(j=0 ; j<COL ; j++){
      if(rcvd_matrix[i][j] == OFF)
        printf(". ");
      else
        printf("x ");
    }
    PRINTBLANKLINE;
  }

  PRINTBLANKLINE;
}

void* client_matrix_thread(void* thread_args){
  //printf("\n CLIENT MATRIX THREAD\n");
  int rcvd_matrix[ROW][COL];
  int bytesread = 0;
  
  while(true){
    bytesread = read(client_sockfd, rcvd_matrix, MATRIXSIZE); /* get matrix from server */
    if(bytesread == 0)
      continue;
    else if(bytesread == MATRIXSIZE){
      //print_matrix_client((int**) rcvd_matrix);
      int i,j;
      for(i=0 ; i<ROW ; i++){
        PRINTTAB;
        for(j=0 ; j<COL ; j++){
          if(rcvd_matrix[i][j] == OFF)
        printf(". ");
      else
        printf("x ");
    }
    PRINTBLANKLINE;
  }

    }
   
  }
}

void send_command_srv(int client_socket, const char* command){
  int comm_len = strlen(command) + 1;
  write(client_socket, &comm_len, sizeof(comm_len)); /* send length */
  write(client_socket, command, comm_len);
}

void start_client(){
  /*
    - create matrix print thread
    - main thread - create socket and connect to server
    - main thread - create a loop to accept user input and send to server
    - matrix thread - wait for data from server and print
  */

  char command[COMMANDSIZE];
  
  pthread_t matrixcthread_id;
  pthread_create(&matrixcthread_id, NULL, &client_matrix_thread, NULL);

  client_sockfd = connect_to_server();
  
  print_help();
  
  while(true){
    scanf("%s",command);
    send_command_srv(client_sockfd, command);
  }
  
}

void server_send_client(Count reps, Mattype matrix_type){
 
  while(true){
    if(reps == STOP)
      return;
    printf("sending to client\n");
    write(client_sockfd_srv, matrix_srv, MATRIXSIZE);

    if(reps == ONCE)
      return;
  }
}

void server_calc_matrix(char* command){

  switch(command[0]){
  case '.': server_send_client(ONCE, DEFAULTMAT);
    break;
  case 'n':
  case 'i':
  case 'r':
  case 'o':
  case 's':
  case 'g':
  case 't':
    break;
  default:
    break;
      
  }

  command[0] = '\0';
}

void* server_matrix_thread(void* thread_args){
  printf("\n SERVER MATRIX THREAD\n");
  //char clncommcpy[COMMANDSIZE];

  init_matrix();
  print_matrix_srv();
  
  while(true){
    pthread_mutex_lock(&clncomm_mutex);
    //strcpy(clncommcpy, (const char*) clncomm);
    

    if(clncomm[0] == 'h')
      continue;
    else if(clncomm[0] == 'q')
      close(client_sockfd_srv);
    else if(clncomm[0] == 'k')
      exit(0);
    else
      server_calc_matrix(clncomm);
    
    clncomm[0] = '\0';
    pthread_mutex_unlock(&clncomm_mutex);
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
  int bytesread = 0;
  
  while(true){

    bytesread = read(client_sockfd_srv, &len, sizeof(len));
    if(bytesread == 0)
      return;
    
    comm = (char*) malloc(len);
    
    read(client_sockfd_srv, comm, len);

    if(bytesread != 0){
      printf("Server received len = %d command = %s\n",len,comm);
      pthread_mutex_lock(&clncomm_mutex);
      strcpy(clncomm,comm);
      pthread_mutex_unlock(&clncomm_mutex);      
    }

    free(comm);
    len=0;
  }
}


void start_server(){
  printf("\n SERVER \n");
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
