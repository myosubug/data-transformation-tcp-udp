/* 
 * TCP_Master.cpp
 * CPSC441 Assignment 2
 * Author: Sungjong Oh
 * Student ID#: 00500426
 */

#include <unistd.h> 
#include <stdio.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>  

#define MAX_BUFFER_SIZE 100

using namespace std;

void initializingAddress();
void creatingSockets();
void UDP_Server_1(char message[], char *b);
void UDP_Server_2(char message[], char *b);
void UDP_Server_3(char message[], char *b);
void UDP_Server_4(char message[], char *b);
void UDP_Server_5(char message[], char *b);
void UDP_Server_6(char message[], char *b);
/*
void interpretCommand(char *command);
*/

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
	char message[MAX_BUFFER_SIZE];
	while (1) {
		count = recv(TCP_connect_socket, message, 100, 0);
		if (count == -1){
			printf("recv() call failed\n");
			exit(-1);
		} else {
			if (strstr(message, "quit") != NULL){
				exit(-1);
			}
			printf("received '%s' from client\n", message);
			printf("sending '%s' to UDP Server 1\n", message);
			bzero(buffer, MAX_BUFFER_SIZE);
			
			
			UDP_Server_2(message, buffer);
			UDP_Server_1(buffer, buffer);
			UDP_Server_5(buffer, buffer);
			UDP_Server_3(buffer, buffer);
			//UDP_Server_4(message, buffer);
			
			//UDP_Server_6(message, buffer);
			
          	//buffer[readBytes] = '\0';    // proper null-termination of string
		  

		}
		printf("Received message from to UDP Server 1!\n");
		count = send(TCP_connect_socket, buffer, 100, 0);
		if (count == -1){
			printf("send() call failed");
			exit(-1);
		}

	}

	//close sockets
	printf("Closing socket...\n");
	close(TCP_connect_socket);
	close(TCP_listen_socket);
	return 0;
}

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


void UDP_Server_1(char message[], char *buffer) {
	if (sendto(UDP_listen_socket_1, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_1, len) == -1){
			printf("sendto failed\n");
			exit(-1);
        }

	if ((readBytes=recvfrom(UDP_listen_socket_1, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_1, &len))==-1){
        	printf("Read error!\n");
            exit(-1);
        }
	//printf("buffer is: %s\n", buffer);
}

void UDP_Server_2(char message[], char *buffer) {
	if (sendto(UDP_listen_socket_2, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_2, len) == -1){
			printf("sendto failed\n");
			exit(-1);
        }

	if ((readBytes=recvfrom(UDP_listen_socket_2, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_2, &len))==-1){
        	printf("Read error!\n");
            exit(-1);
        }
	//printf("buffer is: %s\n", buffer);
}

void UDP_Server_3(char message[], char *buffer) {
	if (sendto(UDP_listen_socket_3, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_3, len) == -1){
			printf("sendto failed\n");
			exit(-1);
        }

	if ((readBytes=recvfrom(UDP_listen_socket_3, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_3, &len))==-1){
        	printf("Read error!\n");
            exit(-1);
        }
	//printf("buffer is: %s\n", buffer);
}

void UDP_Server_4(char message[], char *buffer) {
	if (sendto(UDP_listen_socket_4, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_4, len) == -1){
			printf("sendto failed\n");
			exit(-1);
        }

	if ((readBytes=recvfrom(UDP_listen_socket_4, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_4, &len))==-1){
        	printf("Read error!\n");
            exit(-1);
        }
	//printf("buffer is: %s\n", buffer);
}

void UDP_Server_5(char message[], char *buffer) {
	if (sendto(UDP_listen_socket_5, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_5, len) == -1){
			printf("sendto failed\n");
			exit(-1);
        }

	if ((readBytes=recvfrom(UDP_listen_socket_5, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_5, &len))==-1){
        	printf("Read error!\n");
            exit(-1);
        }
	//printf("buffer is: %s\n", buffer);
}

void UDP_Server_6(char message[], char *buffer) {
	if (sendto(UDP_listen_socket_6, message, strlen(message), 0, (struct sockaddr *) &UDP_server_address_6, len) == -1){
			printf("sendto failed\n");
			exit(-1);
        }

	if ((readBytes=recvfrom(UDP_listen_socket_6, buffer, MAX_BUFFER_SIZE, 0, (struct sockaddr *) &UDP_server_address_6, &len))==-1){
        	printf("Read error!\n");
            exit(-1);
        }
	//printf("buffer is: %s\n", buffer);
}