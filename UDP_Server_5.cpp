/* 
 * UDP_Server_5.cpp
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
#include <ctype.h>

#define MAX_BUFFER_SIZE  1000
#define MASTER_PORT 5000

using namespace std;


void cypher (char *str)
{
	int l = strlen(str);
	const char *alpha[2] = { "abcdefghijklmnopqrstuvwxyz", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
 
	int i;
	for (i = 0; i < l; i++)
	{
		if (!isalpha(str[i]))
			continue;
 
		if (isupper(str[i]))
                        str[i] = alpha[1][((int)(tolower(str[i]) - 'a') + 13) % 26];
                else
                        str[i] = alpha[0][((int)(tolower(str[i]) - 'a') + 13) % 26];
	}
}


int main(int argc, char* argv[]){

	int UDP_PORT_5 = 6005;
    char messagein[MAX_BUFFER_SIZE];
    char messageout[MAX_BUFFER_SIZE];
    int readBytes;
    

	//address initialization	
	printf("Initializing address...\n");
	struct sockaddr_in UDP_server_address_1;
	memset(&UDP_server_address_1, 0, sizeof(UDP_server_address_1));
	UDP_server_address_1.sin_family = AF_INET; //specifies the address family
	UDP_server_address_1.sin_port = htons(UDP_PORT_5); //specificies the port number
	UDP_server_address_1.sin_addr.s_addr = htonl(INADDR_ANY); //specifies the IP address

    struct sockaddr_in client_address;
	memset(&client_address, 0, sizeof(client_address));
	client_address.sin_family = AF_INET; //specifies the address family
	client_address.sin_port = htons(MASTER_PORT); //specificies the port number
	client_address.sin_addr.s_addr = htonl(INADDR_ANY); //specifies the IP address

    socklen_t len = sizeof(UDP_server_address_1);
	//socket creation for TCP server - client and UDPs

	printf("Creating UDP sockets...\n");
	int UDP_SOCKET_5;
	UDP_SOCKET_5 = socket(AF_INET, SOCK_DGRAM, 0);
	if (UDP_SOCKET_5 == -1){
		printf("UDP 1 socket() call failed");
		exit(-1);
	}

	//binding
	printf("Binding...\n");
	int status;
	status = bind(UDP_SOCKET_5, (struct sockaddr *)&UDP_server_address_1, sizeof(struct sockaddr_in));
	if (status == -1){
		printf("bind() call failed\n");
		exit(-1);
	}


	//send and receive information
	printf("Connection successful! Echoing information...\n");
	while (1) {

        bzero(messagein, MAX_BUFFER_SIZE);
	    bzero(messageout, MAX_BUFFER_SIZE);

        if ((readBytes=recvfrom(UDP_SOCKET_5, messagein, MAX_BUFFER_SIZE, 0, (struct sockaddr *)&client_address, &len)) < 0)
	    {
	        printf("Read error!\n");
	        return -1;
	    }
        
        printf("Server received '%s'\n", messagein);
        printf("Server received %d bytes\n", readBytes);
		cypher(messagein);
        printf("Server sending '%s' back\n", messagein);

        sendto(UDP_SOCKET_5, messagein, strlen(messagein), 0, (struct sockaddr *)&client_address, len);	
        
    } 


	//close sockets
	printf("Closing socket...\n");
	close(UDP_SOCKET_5);
	return 0;
}
