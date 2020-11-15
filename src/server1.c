#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
	int server_fd;
	struct sockaddr_in address;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// bind
	if(bind(server_fd, (struct sockaddr*) &address, sizeof(address)) != 0) {
		perror("Failed to bind to port\n");
		exit(1);
	}

	// listen
	if(listen(server_fd, 100) != 0) {
		perror("Failed to start listening\n");
		exit(1);
	}

	// accept
	struct sockaddr_in client_address;
	socklen_t client_address_length = sizeof(client_address);
	int client_fd = accept(server_fd, (struct sockaddr*) &client_address, &client_address_length);
	if(client_fd == -1) {
		perror("error connecting client");
		exit(1);
	}

	int16_t client_ip = ntohs(client_address.sin_addr.s_addr);

	printf("client ip: %i", client_ip);
	
	// receive
	char buff[255];
	read(client_fd, buff, 255); 

	// send
	char message[] = "Hello from server!\0";
	send(client_fd, message, strlen(message), 0);
	
	close(server_fd);
}
