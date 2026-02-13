#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>



void client(char *ip, int port)
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockFd < 0){
        perror("socket error\n");
        exit(1);
    }

    int maxFd = sockFd > STDIN_FILENO ? sockFd : STDIN_FILENO;
    fd_set readSet;
    char buffer[1024] = {0};
    while(1){
        FD_ZERO(&readSet);
        FD_SET(sockFd, &readSet);
        FD_SET(STDIN_FILENO, &readSet);
        int ret = select(maxFd + 1, &readSet, NULL, NULL, NULL);
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
                sendto(sockFd, buffer, 0, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
            }; // EOF

            int ret = sendto(sockFd, buffer, read_len, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
            if(ret <0){
                perror("sendto error\n");
                continue;
            }
        }

        if(FD_ISSET(sockFd, &readSet)){
            memset(buffer, 0, sizeof(buffer));
            struct sockaddr_in server_addr;
            socklen_t server_addr_len = sizeof(server_addr);
            ssize_t ret = recvfrom(sockFd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &server_addr_len);
            if(ret < 0){
                perror("recvfrom error\n");
                continue;
            }else if(ret == 0){
                printf("Server disconnected\n");
                break;
            }else{
                buffer[ret] = '\0';
                printf("Received from server: ip=%s, port=%d, buf=%s",
                    inet_ntoa(server_addr.sin_addr),   ntohs(server_addr.sin_port),   buffer);
            }
        }

    }                         

}


int main(int argc,char *argv[])
{

    if(argc != 3){
        printf("argc error\n");
        return -1;
    }

    client(argv[1],atoi(argv[2]));

    return 0;

}