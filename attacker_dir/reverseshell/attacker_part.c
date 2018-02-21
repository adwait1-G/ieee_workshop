#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>

/*
 *
 * Ideally , the IP Address of the attacker part should be hard-coded or finite number of options shoudl be given.
 * But here , as we try is so many times , the ports become hard to bind. 
 * That is why , We are using command line argument.
 */


void err_exit(const char *errmsg) {

	fprintf(stderr , "%s\n" , errmsg);
	exit(1);
}

int main(int argc , char **argv) {

	if(argc != 3) {
		fprintf(stderr , "Usage: $%s <serveripaddr> <port> \n" , argv[0]);
		exit(1);
	}
	int listen_sockfd;
	if((listen_sockfd = socket(PF_INET , SOCK_STREAM , IPPROTO_TCP)) == -1)
		err_exit("Error in socket()");

	struct sockaddr_in serveraddr;
	memset(&serveraddr , '\0' , sizeof(serveraddr));
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1] , serveraddr.sin_addr);
	unsigned int serveraddrlen = sizeof(serveraddr);

	struct sockaddr_in clientaddr;
	memset(&clientaddr , '\0' , sizeof(clientaddr));
	unsigned int clientaddrlen = sizeof(clientaddr);

	if(bind(listen_sockfd , (struct sockaddr *)&serveraddr , serveraddrlen) == -1)
		err_exit("Error in bind()");

	if(listen(listen_sockfd , 1) == -1)
		err_exit("Error in listen()");

	int new_sockfd;
	if((new_sockfd = accept(listen_sockfd , (struct sockaddr *)&clientaddr , &clientaddrlen)) == -1)
		err_exit("Error in accept()");

	char sendbuffer[100];
	char recvbuffer[10000];
	memset(sendbuffer,  '\0' , 100);
	memset(recvbuffer , '\0' , 10000);


	int forkvalue;
	if((forkvalue = fork()) == 0) {
		
		while(1) {

			read(0 , sendbuffer , 100);
			if(send(new_sockfd , sendbuffer , strlen(sendbuffer) , 0) == -1)
				err_exit("Error in send()");
			memset(sendbuffer , '\0' , 100);
		}
	}
	else if(forkvalue > 0) {
		while(1) {

			if(recv(new_sockfd , recvbuffer , 10000 , 0) == -1)
				err_exit("Error in recv()");

			write(1 , recvbuffer , strlen(recvbuffer));

			memset(recvbuffer , '\0' , 10000);
		}
	}
	else
		err_exit("Error in fork()");

	close(listen_sockfd);
	close(new_sockfd);

	return 0;
}

















