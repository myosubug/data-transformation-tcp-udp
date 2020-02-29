
#include <iostream>
#include <unistd.h> 
#include <stdio.h>
#include <sys/socket.h> 
#include <sys/select.h>
#include <sys/types.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <string>
#include <strings.h>
#include <stddef.h>
#include <sys/time.h>

#define MAX_BUFFER_SIZE 1000

using namespace std;

//declaring methods
void initializingAddress();
void creatingSockets();
void UDP_Server_1(char message[], char *b);
void UDP_Server_2(char message[], char *b);
void UDP_Server_3(char message[], char *b);
void UDP_Server_4(char message[], char *b);
void UDP_Server_5(char message[], char *b);
void UDP_Server_6(char message[], char *b);
void interpretCommand(char sentence[], char command[], char *buffer);

//prestting global variables
struct sockaddr_in TCP_server_address;
struct sockaddr_in UDP_server_address_1;
struct sockaddr_in UDP_server_address_2;
struct sockaddr_in UDP_server_address_3;
struct sockaddr_in UDP_server_address_4;
struct sockaddr_in UDP_server_address_5;
struct sockaddr_in UDP_server_address_6;
int TCP_PORT = 5000;
int UDP_PORT_1 = 6001;
int UDP_PORT_2 = 6002;
int UDP_PORT_3 = 6003;
int UDP_PORT_4 = 6004;
int UDP_PORT_5 = 6005;
int UDP_PORT_6 = 6006;
int TCP_listen_socket;
int UDP_listen_socket_1;
int UDP_listen_socket_2;
int UDP_listen_socket_3;
int UDP_listen_socket_4;
int UDP_listen_socket_5;
int UDP_listen_socket_6;
char buffer[MAX_BUFFER_SIZE];
int readBytes;
int server;
socklen_t len;


int main(int argc, char* argv[]){


    char buffer[MAX_BUFFER_SIZE];
    int readBytes;
	initializingAddress();
	creatingSockets();
	len = sizeof(UDP_server_address_1);

	//binding
	printf("Binding...\n");
	int status;
	status = bind(TCP_listen_socket, (struct sockaddr *)&TCP_server_address, sizeof(struct sockaddr_in));
	if (status == -1){
		printf("bind() call failed\n");
		exit(-1);
	}

	//listening
	status = listen(TCP_listen_socket, 5);
	printf("Listening...\n");
	if (status == -1){
		printf("listen() call failed");
		exit(-1);
	}

	//accept connection
	int TCP_connect_socket;
	TCP_connect_socket = accept(TCP_listen_socket, NULL, NULL);
	printf("Accepting connection...\n");
	if (TCP_connect_socket == -1){
		printf("accept() call failed\n");
		exit(-1);
	}

	//send and receive information
	printf("Connection successful! Echoing information...\n");
	int count;
	string temp;
	string sent;
	string comm;
	char message[MAX_BUFFER_SIZE];
	char sentence[MAX_BUFFER_SIZE];
	char command[MAX_BUFFER_SIZE];
	while (1) {

		//cleaning up variables
		bzero(sentence, MAX_BUFFER_SIZE);
		bzero(command, MAX_BUFFER_SIZE);
		
		//receving requests form TCP client
		count = recv(TCP_connect_socket, message, 1000, 0);
		if (count == -1){
			printf("recv() call failed\n");
			exit(-1);
		} else {
			printf("received '%s' from client\n", message);

			//parsing TCP client requests into message and commands
			temp = message;
			int token = temp.find("@");
			sent = temp.substr(0, token);
			comm = temp.substr(token+1, strlen(message)-1);
			strcpy(sentence, sent.c_str());
			strcpy(command, comm.c_str());
		}

		bzero(buffer, MAX_BUFFER_SIZE);

		//interpreting commands with the requested message
		interpretCommand(sentence, command, buffer);

		//sending processed message back to TCP client
		count = send(TCP_connect_socket, buffer, 1000, 0);
		if (count == -1){
			printf("send() call failed");
			exit(-1);
		}

		if (strstr(message, "quit") != NULL){
			break;
		}

	}

	//close sockets
	printf("Closing socket...\n");
	close(TCP_connect_socket);
	close(TCP_listen_socket);
	return 0;
}

//factoring all initilization of addresses
void initializingAddress(){
	printf("Initializing address...\n");
	memset(&TCP_server_address, 0, sizeof(TCP_server_address));
	TCP_server_address.sin_family = AF_INET; //specifies the address family
	TCP_server_address.sin_port = htons(TCP_PORT); //specificies the port number
	TCP_server_address.sin_addr.s_addr = htonl(INADDR_ANY); //specifies the IP address

	memset(&UDP_server_address_1, 0, sizeof(UDP_server_address_1));
	UDP_server_address_1.sin_family = AF_INET; //specifies the address family
	UDP_server_address_1.sin_port = htons(UDP_PORT_1); //specificies the port number
	UDP_server_address_1.sin_addr.s_addr = htonl(INADDR_ANY); //specifies the IP address

	memset(&UDP_server_address_2, 0, sizeof(UDP_server_address_2));
	UDP_server_address_2.sin_family = AF_INET; //specifies the address family
	UDP_server_address_2.sin_port = htons(UDP_PORT_2); //specificies the port number
	UDP_server_address_2.sin_addr.s_addr = htonl(INADDR_ANY); //specifies the IP address

	memset(&UDP_server_address_3, 0, sizeof(UDP_server_address_3));
	UDP_server_address_3.sin_family = AF_INET; //specifies the address family
	UDP_server_address_3.sin_port = htons(UDP_PORT_3); //specificies the port number
	UDP_server_address_3.sin_addr.s_addr = htonl(INADDR_ANY); //specifies the IP address

	memset(&UDP_server_address_4, 0, sizeof(UDP_server_address_4));
	UDP_server_address_4.sin_family = AF_INET; //specifies the address family
	UDP_server_address_4.sin_port = htons(UDP_PORT_4); //specificies the port number
	UDP_server_address_4.sin_addr.s_addr = htonl(INADDR_ANY); //specifies the IP address

	memset(&UDP_server_address_5, 0, sizeof(UDP_server_address_5));
	UDP_server_address_5.sin_family = AF_INET; //specifies the address family
	UDP_server_address_5.sin_port = htons(UDP_PORT_5); //specificies the port number
	UDP_server_address_5.sin_addr.s_addr = htonl(INADDR_ANY); //specifies the IP address

	memset(&UDP_server_address_6, 0, sizeof(UDP_server_address_6));
	UDP_server_address_6.sin_family = AF_INET; //specifies the address family
	UDP_server_address_6.sin_port = htons(UDP_PORT_6); //specificies the port number
	UDP_server_address_6.sin_addr.s_addr = htonl(INADDR_ANY); //specifies the IP address
}

//factoring all socket creations
void creatingSockets(){
	printf("Creating TCP socket...\n");
	TCP_listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (TCP_listen_socket == -1){
		printf("TCP socket() call failed");
		exit(-1);
	}

	printf("Creating 6 UDP sockets...\n");
	UDP_listen_socket_1 = socket(AF_INET, SOCK_DGRAM, 0);
	if (UDP_listen_socket_1 == -1){
		printf("UDP 1 socket() call failed");
		exit(-1);
	}

	UDP_listen_socket_2 = socket(AF_INET, SOCK_DGRAM, 0);
	if (UDP_listen_socket_2 == -1){
		printf("UDP 2 socket() call failed");
		exit(-1);
	}

	UDP_listen_socket_3 = socket(AF_INET, SOCK_DGRAM, 0);
	if (UDP_listen_socket_3 == -1){
		printf("UDP 3 socket() call failed");
		exit(-1);
	}

	UDP_listen_socket_4 = socket(AF_INET, SOCK_DGRAM, 0);
	if (UDP_listen_socket_4 == -1){
		printf("UDP 4 socket() call failed");
		exit(-1);
	}

	UDP_listen_socket_5 = socket(AF_INET, SOCK_DGRAM, 0);
	if (UDP_listen_socket_5 == -1){
		printf("UDP 5 socket() call failed");
		exit(-1);
	}

	UDP_listen_socket_6 = socket(AF_INET, SOCK_DGRAM, 0);
	if (UDP_listen_socket_6 == -1){
		printf("UDP 6 socket() call failed");
		exit(-1);
	}

	int enable = 1;
	if (setsockopt(TCP_listen_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    	perror("setsockopt(SO_REUSEADDR) failed");
}

//factoring UDP server call
void UDP_Server_1(char message[], char *buffer) {
	fd_set select_fds;                /* fd's used by select */
	struct timeval timeout;           /* Time value for time out */
	timeout.tv_sec = 5;         /* Timeout set for 5 sec + 0 micro sec*/
	timeout.tv_usec = 0;

	FD_ZERO(&select_fds);             /* Clear out fd's */
    FD_SET(UDP_listen_socket_1, &select_fds);           /* Set the bit that corresponds to
                                           socket s        */

	if (sendto(UDP_listen_socket_1, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_1, len) == -1){
			printf("sendto failed\n");
			exit(-1);
	}

	if (select(32, &select_fds, NULL, NULL, &timeout) == 0 ){
         printf("UDP Server 1 has timed out!\nCheck if UDP server 1 is working\nTerminating Master Server..\n");
		 exit(-1);
      	}
    else{
		if ((readBytes=recvfrom(UDP_listen_socket_1, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_1, &len))==-1){
			printf("Read error!\n");
			exit(-1);
		}
	}
}

void UDP_Server_2(char message[], char *buffer) {
	fd_set select_fds;                /* fd's used by select */
	struct timeval timeout;           /* Time value for time out */
	timeout.tv_sec = 5;         /* Timeout set for 5 sec + 0 micro sec*/
	timeout.tv_usec = 0;

	FD_ZERO(&select_fds);             /* Clear out fd's */
    FD_SET(UDP_listen_socket_2, &select_fds);           /* Set the bit that corresponds to
                                           socket s        */

	if (sendto(UDP_listen_socket_2, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_2, len) == -1){
			printf("sendto failed\n");
			exit(-1);
	}

	if (select(32, &select_fds, NULL, NULL, &timeout) == 0 ){
         printf("UDP Server 2 has timed out!\nCheck if UDP server 2 is working\nTerminating Master Server..\n");
		 exit(-1);
      	}
    else{
		if ((readBytes=recvfrom(UDP_listen_socket_2, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_2, &len))==-1){
			printf("Read error!\n");
			exit(-1);
		}
	}
}

void UDP_Server_3(char message[], char *buffer) {

	fd_set select_fds;                /* fd's used by select */
	struct timeval timeout;           /* Time value for time out */
	timeout.tv_sec = 5;         /* Timeout set for 5 sec + 0 micro sec*/
	timeout.tv_usec = 0;

	FD_ZERO(&select_fds);             /* Clear out fd's */
    FD_SET(UDP_listen_socket_3, &select_fds);           /* Set the bit that corresponds to
                                           socket s        */

	if (sendto(UDP_listen_socket_3, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_3, len) == -1){
			printf("sendto failed\n");
			exit(-1);
	}

	if (select(32, &select_fds, NULL, NULL, &timeout) == 0 ){
         printf("UDP Server 3 has timed out!\nCheck if UDP server 3 is working\nTerminating Master Server..\n");
		 exit(-1);
      	}
    else{
		if ((readBytes=recvfrom(UDP_listen_socket_3, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_3, &len))==-1){
			printf("Read error!\n");
			exit(-1);
		}
	}
}

void UDP_Server_4(char message[], char *buffer) {
	fd_set select_fds;                /* fd's used by select */
	struct timeval timeout;           /* Time value for time out */
	timeout.tv_sec = 5;         /* Timeout set for 5 sec + 0 micro sec*/
	timeout.tv_usec = 0;

	FD_ZERO(&select_fds);             /* Clear out fd's */
    FD_SET(UDP_listen_socket_4, &select_fds);           /* Set the bit that corresponds to
                                           socket s        */

	if (sendto(UDP_listen_socket_4, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_4, len) == -1){
			printf("sendto failed\n");
			exit(-1);
    }
	if (select(32, &select_fds, NULL, NULL, &timeout) == 0 ){
         printf("UDP Server 4 has timed out!\nCheck if UDP server 4 is working\nTerminating Master Server..\n");
		 exit(-1);
      	}
    else{
		if ((readBytes=recvfrom(UDP_listen_socket_4, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_4, &len))==-1){
        	printf("Read error!\n");
            exit(-1);
    	}
	}
}

void UDP_Server_5(char message[], char *buffer) {

	fd_set select_fds;                /* fd's used by select */
	struct timeval timeout;           /* Time value for time out */
	timeout.tv_sec = 5;         /* Timeout set for 5 sec + 0 micro sec*/
	timeout.tv_usec = 0;

	FD_ZERO(&select_fds);             /* Clear out fd's */
    FD_SET(UDP_listen_socket_5, &select_fds);           /* Set the bit that corresponds to
                                           socket s        */

	if (sendto(UDP_listen_socket_5, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_5, len) == -1){
			printf("sendto failed\n");
			exit(-1);
    }
	if (select(32, &select_fds, NULL, NULL, &timeout) == 0 ){
         printf("UDP Server 5 has timed out!\nCheck if UDP server 5 is working\nTerminating Master Server..\n");
		 exit(-1);
      	}
    else{
		if ((readBytes=recvfrom(UDP_listen_socket_5, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_5, &len))==-1){
        	printf("Read error!\n");
            exit(-1);
    	}
	}
}

void UDP_Server_6(char message[], char *buffer) {
	fd_set select_fds;                /* fd's used by select */
	struct timeval timeout;           /* Time value for time out */
	timeout.tv_sec = 5;         /* Timeout set for 5 sec + 0 micro sec*/
	timeout.tv_usec = 0;

	FD_ZERO(&select_fds);             /* Clear out fd's */
    FD_SET(UDP_listen_socket_6, &select_fds);           /* Set the bit that corresponds to
                                           socket s        */

	if (sendto(UDP_listen_socket_6, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_6, len) == -1){
			printf("sendto failed\n");
			exit(-1);
	}

	if (select(32, &select_fds, NULL, NULL, &timeout) == 0 ){
         printf("UDP Server 6 has timed out!\nCheck if UDP server 6 is working\nTerminating Master Server..\n");
		 exit(-1);
      	}
    else{
		if ((readBytes=recvfrom(UDP_listen_socket_6, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_6, &len))==-1){
			printf("Read error!\n");
			exit(-1);
		}
	}
}

//interpreting requested command one by one by interation and switch statements
void interpretCommand(char sentence[], char command[], char *buffer){

	switch (command[0]) {
		case '1':
			UDP_Server_1(sentence, buffer);
			break;
		case '2':
			UDP_Server_2(sentence, buffer);
			break;
		case '3':
			UDP_Server_3(sentence, buffer);
			break;
		case '4':
			UDP_Server_4(sentence, buffer);
			break;
		case '5':
			UDP_Server_5(sentence, buffer);
			break;
		case '6':
			UDP_Server_6(sentence, buffer);
			break;
	}
		
	for(int i = 1; i < strlen(command); ++i){
		switch (command[i]) {
			case '1':
				UDP_Server_1(buffer, buffer);
				break;
			case '2':
				UDP_Server_2(buffer, buffer);
				break;
			case '3':
				UDP_Server_3(buffer, buffer);
				break;
			case '4':
				UDP_Server_4(buffer, buffer);
				break;
			case '5':
				UDP_Server_5(buffer, buffer);
				break;
			case '6':
				UDP_Server_6(buffer, buffer);
				break;
		}
	}
	
 }

 