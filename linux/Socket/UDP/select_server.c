#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

/* 利用select实现UDP的即时通信服务器 */

void server(char *ip, int port)
{
    struct sockaddr_in server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);


    int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockFd < 0){
        perror("socket error\n");
        exit(1);
    }
    int pause = 1;
    int ret = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &pause, sizeof(pause));
    if(ret < 0){
        perror("setsockopt error\n");
        exit(1);
    }
    ret = bind(sockFd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret < 0){
        perror("bind error\n");
        exit(1);
    }

    int maxFd = sockFd > STDIN_FILENO ? sockFd : STDIN_FILENO;
    fd_set readSet;
    char buffer[1024] = {0};
    while(1){
        FD_ZERO(&readSet);
        FD_SET(sockFd, &readSet);
        FD_SET(STDIN_FILENO, &readSet);
        ret = select(maxFd + 1, &readSet, NULL, NULL, NULL);
        if(ret < 0){
            perror("select error\n");
            exit(1);
        }


        if(FD_ISSET(STDIN_FILENO, &readSet)){
            memset(buffer, 0, sizeof(buffer));
            ssize_t read_len = read(STDIN_FILENO, buffer, sizeof(buffer));
            if(read_len < 0){
                perror("read error\n");
                exit(1);
            }

            if(read_len == 0) {
                sendto(sockFd, buffer, 0, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
            }; // EOF

            int ret = sendto(sockFd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
            if(ret <0){
                perror("sendto error\n");
                continue;
            }
        }

        if(FD_ISSET(sockFd, &readSet)){
            memset(buffer, 0, sizeof(buffer));
            socklen_t client_addr_len = sizeof(client_addr);
            ssize_t ret = recvfrom(sockFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_len);
            if(ret < 0){
                perror("recvfrom error\n");
                continue;
            }else if(ret == 0){
                printf("Client disconnected\n");
                break;
            }else{
                printf("Received from client: ip=%s, port=%d, buf=%s",
                    inet_ntoa(client_addr.sin_addr),   ntohs(client_addr.sin_port),   buffer);
            }
        }

    }

    close(sockFd);

}

int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("argc error\n");
        return -1;
    }

    server(argv[1], atoi(argv[2]));

    return 0;
}