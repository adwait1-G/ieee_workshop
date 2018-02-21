#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<netinet/in.h>

int  main(int argc , char **argv) {

	if(argc != 3) {
		fprintf(stderr , "Usage: $%s <ipaddr> <port>\n" , argv[0]);
		exit(1);
	}

	int sockfd;
	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1] , serveraddr.sin_addr);

	sockfd = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
	connect(sockfd , (struct sockaddr *)&serveraddr , sizeof(serveraddr));

	char sendbuffer[20];
	char recvbuffer[10000];

	if(fork() == 0) {

		while(1) {
			memset(sendbuffer , '\0' , 20);
			write(1 , ">>>" , sizeof(">>>"));

			read(0 , sendbuffer , sizeof(sendbuffer));
			send(sockfd , sendbuffer , sizeof(sendbuffer) , 0);
		}
	}

	else {
		while(1) {
			memset(recvbuffer , '\0' , 10000);
			recv(sockfd , recvbuffer , sizeof(recvbuffer) , 0);
			write(1 , recvbuffer , sizeof(recvbuffer));
			write(1 , ">>>" , sizeof(">>>"));
		}
	}

	return 0;
}





		


