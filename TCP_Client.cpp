/* 
 * TCP_Client.cpp
 * CPSC441 Assignment 2
 * Author: Sungjong Oh
 * Student ID#: 00500426
 */
#include <iostream>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 

#define MAX_BUFFER_SIZE 1000

using namespace std;

int main(int argc, char* argv[]){
	//address initialization
	printf("Initializing address...\n");
	int TCP_PORT = 5000;
	struct sockaddr_in client_address;
	memset(&client_address, 0, sizeof(client_address));
	client_address.sin_family = AF_INET; //specifies the address family
	client_address.sin_port = htons(TCP_PORT); //specificies the port number
	client_address.sin_addr.s_addr = htonl(INADDR_ANY); //specifies the IP address

	//socket creation
	printf("Creating socket...\n");
	int connect_socket;
	connect_socket = socket(AF_INET, SOCK_STREAM, 0);
	//check if socket creation was successful
	if (connect_socket == -1){
		printf("socket() call failed");
		exit(-1);
	}

	//connection request
	printf("Sending connection request...\n");
	int status;
	status = connect(connect_socket, (struct sockaddr*)&client_address, sizeof(struct sockaddr_in));
	//check if connection was successful
	if (status == -1){
		printf("connect() call failed");
		exit(-1);
	}

	//send and receive information
	printf("Connection successful! Enter 'quit' to end program.\n");
	int count;
	char send_message[85];
	char send_command[14];
	char combine_message[MAX_BUFFER_SIZE];
	char receive_message[MAX_BUFFER_SIZE];
	while (1) {
		bzero(send_message, 85);
		bzero(send_command, 14);
		bzero(receive_message, MAX_BUFFER_SIZE);
		bzero(combine_message, MAX_BUFFER_SIZE);

		printf("Enter message to send: ");
		gets(send_message);
		printf("Enter a command/commands to operate on the message:\n1:Identity(Echo Back)\n2:Reverse\n3:To upper case\n4:To lower case\n5:Caesar\n6:Camel case\nFor example, you can also try multiple operations such as '2135'\nEnter command: ");
		gets(send_command);
		strcpy(combine_message,send_message);
		combine_message[strlen(combine_message)] = '@';
    	strcat(combine_message,send_command);


		count = send(connect_socket, combine_message, 100, 0);
		if (count == -1){
			printf("send() call failed");
			exit(-1);
		}
		count = recv(connect_socket, receive_message, 100, 0);
		if (count == -1){
			printf("recv() call failed\n");
			exit(-1);
		} else {
			cout << endl << endl;
			cout << "===============================" << endl;
			printf("sent '%s' to server\n", send_message);
			printf("received '%s' from server\n", receive_message);
			cout << "===============================" << endl << endl;
		}
		if (strstr("quit", receive_message) != NULL || strstr(send_message, "quit") != NULL){
			break;
		}
		
	}

	//close sockets
	printf("Closing socket...\n");
	close(connect_socket);
	return 0;

}