#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>


#define LISTENQUEUE 1
#define TRUE 1
#define FALSE 0
#define RECVBUFSIZE 500
#define SENDBUFSIZE 500

void application(char *buffer , int new_sockfd);

/*
 * The below routine is the error handling routine.
 */

void err_exit(const char *errmsg) {
	fprintf(stderr , "%s\n" , errmsg);
	exit(1);
}

/*
 * The main() routine , The actual server code.
 */

int main(int argc , char **argv) {

	if(argc != 3) {
		fprintf(stderr , "Usage: $%s <server_ip_addr> <port> \n" , argv[0]);
		exit(1);
	}

	/*
	 * All details about the server .
	 *
	 * 1. serverport: Port behind which the server is running.
	 * 2. serveripaddr: This points to the server IP address.
	 * 3. serveraddr: This is an instance of the structure struct sockaddr_in .
	 * 	
	 * 	struct sockaddr_in {
	 * 		
	 * 		short		sin_family;
	 * 		unsigned short	sin_port;
	 * 		struct in_addr	sin_addr;
	 * 		char 		sin_zero[8];
	 * 	};
	 *
	 * 	struct in_addr {
	 * 		unsigned long s_addr;	
	 * 	};
	 *
	 * Read manpages and /usr/include/netinet/in.h for more details.
	 */

	unsigned short serverport;
	char *serveripaddr;
	struct sockaddr_in serveraddr;
	unsigned int serveraddrlen;

	serveraddrlen = sizeof(serveraddr);
	serverport = atoi(argv[2]);
	serveripaddr = argv[1];
	
	memset(&serveraddr , '\0' , serveraddrlen);
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(serverport);
	inet_aton(serveripaddr , (struct in_addr *)&serveraddr.sin_addr);

	/*
	 * All details about the client which gets connected to the running server.
	 */

	unsigned short clientport;
	char *clientipaddr;
	struct sockaddr_in clientaddr;
	unsigned int clientaddrlen;
	
	clientaddrlen = sizeof(clientaddr);
	memset(&clientaddr , '\0' , clientaddrlen);


	int listen_sockfd;
	
	/*
	 * Creation of a socket using the "socket()" system call.
	 * Returns a non-zero integer on successfully creating the socket.
	 * Returns -1 on failure.
	 * The socket() system call on success is said to return what is known as the "FILE DESCRIPTOR" or "fd" .
	 * Throughout the program , The socket is referenced using this file descriptor or fd.
	 *
	 * Read manpages and /usr/include/sys/socket.h for more details.
	 */

	if((listen_sockfd = socket(PF_INET , SOCK_STREAM , IPPROTO_TCP)) == -1) 
		err_exit("Error in socket()");

	
	/*
	 * The listen_sockfd and server details(which we filled in the beginning) are bound together by the "bind()" system call.
	 * Returns 0 on success , -1 on failure.
	 * 
	 * Read manpages and /usr/include/sys/socket.h for more details.
	 */

	if(bind(listen_sockfd , (struct sockaddr *)&serveraddr , serveraddrlen) == -1)
		err_exit("Error in bind()");

	/*
	 * We know the server details.(IP Address , Port number).
	 * We have the file_descriptor which will be used to refer to the server.
	 * The server should be ready to accept new connections.
	 * To make it ready , use the "listen()" system call.
	 * Returns 0 on success , -1 on failure.
	 *
	 * Very critical system call.This is the system call which differentiates between a server socket and a client socket.
	 * Read manpages and /usr/include/sys/socket.h for more details.
	 */

	if(listen(listen_sockfd , LISTENQUEUE) == -1)
		err_exit("Error in listen()");

	printf("Server[%s , %d] is running\n\n" , serveripaddr , serverport);

	/*
	 * The server is ready and running.
	 * 
	 * To accept any incoming connection , use the "accept()" system call.
	 * On success , It returns a non-negative integer which is the file descriptor used to communicate with the new client which sent the connection request.
	 * On failure , returns -1.
	 *
	 * Read manpages and /usr/include/sys/socket.h for more details.
	 */

	int new_sockfd;
	if((new_sockfd = accept(listen_sockfd , (struct sockaddr *)&clientaddr , &clientaddrlen)) == -1)
		err_exit("Error in accept()");


	/*
	 * Updating client's information.
	 */

	clientport = ntohs(clientaddr.sin_port);
	clientipaddr = inet_ntoa(clientaddr.sin_addr);
	
	printf("Connected to client : [%s , %d] \n" , clientipaddr , clientport);

	/*
	 * Stage 1 : The connection part is done. 
	 * The server and client are connected.
	 *
	 * Next part is the core part , the application part.(The service offered by the server).
	 */

	char recvbuffer[RECVBUFSIZE];
	unsigned int numrecv;
	memset(recvbuffer , '\0' , RECVBUFSIZE);

	char sendbuffer[SENDBUFSIZE];
	unsigned int numsent;
	memset(sendbuffer , '\0' , SENDBUFSIZE);

	/*
	 * To send a message to client , use the "send()" system call.
	 * send(): Returns number of bytes sent on success , -1 on failure.
	 *
	 * To receive a message from the client , use the "recv()" system call.
	 * recv(): Returns number of bytes received on success , -1 on failure and 0 if it has received the EOF(End-Of-File) .
	 *
	 * Refer manpages and /usr/include/sys/socket.h for more details.
	 */ 
	 

	while(TRUE) {

//		if((numsent = send(new_sockfd , "\nEnter a string: " , sizeof("\nEnter a string: ") , 0)) == -1)
//			err_exit("Error in send()");

		printf("Before receiving....\n");
		if((numrecv = read(new_sockfd , recvbuffer , RECVBUFSIZE )) == -1)
			err_exit("Error in recv()");
		printf("numrecv = %d\n" , numrecv);

		application(recvbuffer , new_sockfd);
		printf("Just after application...\n");
		memset(recvbuffer , '\0' , RECVBUFSIZE);

	}

	close(listen_sockfd);
	close(new_sockfd);

	return 0;
}


void application(char *buffer , int new_sockfd) {

	char copyintobuffer[250];
	memset(copyintobuffer , '\0' , sizeof(copyintobuffer));
	printf("%p\n" , copyintobuffer);
	strcpy(copyintobuffer , buffer);
	printf("%s\n , length = %d\n" , copyintobuffer , strlen(copyintobuffer));
}
























