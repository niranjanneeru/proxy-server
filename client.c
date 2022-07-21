# include "network.h"


#define PROXY_PORT 8088
#define IP 0
#define LEN 1024
#define SERVER_PORT 8080

void simulate_get(){
    int client_fd, proxy_fd;
    struct sockaddr_in * address;
    char msg[LEN];
    client_fd = create_socket(AF_INET, SOCK_STREAM, IP);
	address = build_address(AF_INET, PROXY_PORT);
	connect_socket(client_fd,address);
    int port = htons(SERVER_PORT);
    write(client_fd, &port, sizeof(port));
    int id = 1;
    write(client_fd, &id, sizeof(id));
    read(client_fd , msg, LEN);
    printf("GET to Server Msg = %s\n",msg);
    close(client_fd);
}

void simulate_post(){
    int client_fd, proxy_fd;
    int status_code;
    struct sockaddr_in * address;
    char msg[LEN];
    printf("Write in message to POST: ");
    scanf("%s",msg);
    client_fd = create_socket(AF_INET, SOCK_STREAM, IP);
	address = build_address(AF_INET, PROXY_PORT);
	connect_socket(client_fd,address);
    int port = htons(SERVER_PORT);
    write(client_fd, &port, sizeof(port));
    int id = 2;
    write(client_fd, &id, sizeof(id));
    write(client_fd , msg, LEN);
    read(client_fd, &status_code, sizeof(status_code));
    printf("POST to Server Mes = %s & STATUS Code = %d\n",msg, status_code);
    close(client_fd);
}

void main(){
    // simulate_get();
    simulate_post();
}