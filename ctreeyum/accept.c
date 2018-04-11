/******************************************
 * Filename : accept.c
 * Purpose  : creates a socket and allows a simple connection
 * Author   : Simon Amor (simon@leaky.org)
 ***/

#include <stdio.h>

/* for EXIT_FAILURE and EXIT_SUCCESS */
#include <stdlib.h>

/* network functions */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
  int socket_desc;
  struct sockaddr_in address;
  int addrlen;
  int new_socket;

/* create the master socket and check it worked */
  if ((socket_desc=socket(AF_INET,SOCK_STREAM,0))==0)
  {
/* if socket failed then display error and exit */
    perror("Create socket");
    exit(EXIT_FAILURE);
  }

/* type of socket created */
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
/* 7000 is the port to use for connections */
  address.sin_port = htons(7000);
/* bind the socket to port 7000 */
  if (bind(socket_desc,(struct sockaddr *)&address,sizeof(address))<0)
  {
/* if bind failed then display error message and exit */
    perror("bind");
    exit(EXIT_FAILURE);
  }

/* try to specify maximum of 3 pending connections for the master socket */
  if (listen(socket_desc,3)<0)
  {
/* if listen failed then display error and exit */
    perror("listen");
    exit(EXIT_FAILURE);
  }

/* accept one connection, wait if no connection pending */
  addrlen=sizeof(address);
  if ((new_socket=accept(socket_desc,(struct sockaddr *)&address,&addrlen))<0)
  {
/* if accept failed to return a socket descriptor, display error and exit */
    perror("accept");
    exit(EXIT_FAILURE);
  }
/* inform user of socket number - used in send and receive commands */
  printf("New socket is %d\n",new_socket);

sleep(10);

/* shutdown master socket properly */
  close(socket_desc);
}
