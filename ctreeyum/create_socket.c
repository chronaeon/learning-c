#include <sys/types.h>
#include <sys/socket.h>

int main(){;
	
	/*Syntax: 
	 *int socket(int af, int type, int protocol);*/
	
	int socket_desc;

	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if (socket_desc==-1)
		perror("Create socket");

}

