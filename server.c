# include "network.h"

# define PORT 8080
# define IP 0
# define LEN 1024

void main(){
    int server_fd, proxy_fd;
    struct sockaddr_in * address;
    socklen_t peer_addr_size = sizeof(struct sockaddr_in);
    server_fd = create_socket(AF_INET, SOCK_STREAM, IP);
    address = build_address(AF_INET, PORT);
    bind_socket(server_fd, address);
    socket_listen(server_fd, 3);
    start:
    proxy_fd = socket_accept(server_fd, address, peer_addr_size);

    int id;
    int status_code = 200;
    char res[LEN] = "Hello From Server";
    char msg[LEN];
    read(proxy_fd,&id,sizeof(id));
    if(id == 1){
        write(proxy_fd, res, LEN);
        printf("GET Request %s\n", res);
    }else{
        read(proxy_fd, msg, LEN);
        printf("POST Request %s Status Code %d\n", msg, status_code);
        write(proxy_fd, &status_code, sizeof(status_code));
    }
    close(proxy_fd);
    goto start;
}