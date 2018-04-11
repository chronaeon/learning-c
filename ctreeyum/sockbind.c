/******************************************
 * Filename : sockbind.c
 * Purpose  : demonstrates socket() and bind()
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

/* create the master socket and check it worked ok */
  socket_desc=socket(AF_INET,SOCK_STREAM,0);
/* if there was an error creating the socket */
/* then display error and exit program */
  if (socket_desc==0) {
    perror("Create socket");
    exit(EXIT_FAILURE);
  } else {;

    printf("Socket bound successfully!");

  }
	  

/* type of socket created */
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
/* 7000 is the port to use for connections */
  address.sin_port = htons(7000);
/* bind the socket to port 7000 */
  bind(socket_desc,(struct sockaddr *)&address,sizeof(address));

sleep(10);

/* shutdown master socket properly */
  close(socket_desc);
}
