#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <unistd.h>

int create_socket(int domain, int type, int protocol){
    int server_fd = socket(domain, type, protocol);
    if(server_fd != 0) 
        return server_fd;
    perror("Socket Creation Failed");
    exit(EXIT_FAILURE);
}

struct sockaddr_in * build_address(int domain,int port){
		
		struct sockaddr_in * address = malloc(sizeof(struct sockaddr_in));
		address->sin_family = domain;
		address->sin_port = htons(port);
		address->sin_addr.s_addr = INADDR_ANY;
		return address;	
} 

void bind_socket(int server_fd,struct sockaddr_in * address){
	if (bind(server_fd, (struct sockaddr*)address, sizeof(*address)) < 0) {
        perror("Binding Failed");
        exit(EXIT_FAILURE);
    }
}

void socket_listen(int server_fd, int backlog){
	if (listen(server_fd, backlog) < 0) {
        perror("Listen Failed");
        exit(EXIT_FAILURE);
    }
}

int socket_accept(int server_fd,struct sockaddr_in * address,socklen_t sock_size){
	int new_socket = accept(server_fd, (struct sockaddr*)address, &sock_size);
	if (new_socket < 0) {
        perror("Accept Failed");
        exit(EXIT_FAILURE);
    }
    return new_socket;
}

int connect_socket(int sock,struct sockaddr_in * serv_addr){
	int res = connect(sock, (struct sockaddr*)serv_addr,sizeof(*serv_addr));
	if (res < 0) {
        perror("Connect Failed");
        exit(EXIT_FAILURE);
    }
}