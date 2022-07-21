# include "network.h"

# define PORT 8088
# define IP 0
# define LEN 1024

void main(){
    int proxy_fd, client_fd, server_fd;
    struct sockaddr_in * address;
    struct sockaddr_in * server_addr;
    socklen_t peer_addr_size = sizeof(struct sockaddr_in);
    proxy_fd = create_socket(AF_INET, SOCK_STREAM, IP);
    address = build_address(AF_INET, PORT);
    bind_socket(proxy_fd, address);
    socket_listen(proxy_fd, 3);

    start:
    client_fd = socket_accept(proxy_fd, address, peer_addr_size);
    int id;
    int status_code;
    int port;
    char msg[LEN];
    read(client_fd,&port,sizeof(port));
    read(client_fd,&id,sizeof(id));
    server_fd = create_socket(AF_INET, SOCK_STREAM, IP);
    server_addr = build_address(AF_INET, htons(port));
    connect_socket(server_fd,server_addr);
    if(id == 1){
        write(server_fd, &id, sizeof(id));
        read(server_fd, msg, LEN);
        printf("GET to Server %s \n",msg);
        strcat(msg, " Hello From Proxy");
        write(client_fd, msg, LEN);
    }else{
        read(client_fd, msg, LEN);
        printf("POST to Server - %s Awaiting Response Code\n",msg);
        write(server_fd, msg, strlen(msg));
        read(server_fd, &status_code, sizeof(status_code));
        write(client_fd, &status_code, sizeof(status_code));
    }
    close(server_fd);
    close(client_fd);
    goto start;
}