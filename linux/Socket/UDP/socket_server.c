#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/**
 * UDP服务器
 * 1. 创建套接字socket
 * 2. 绑定地址信息bind
 * 3. 进行通信recvfrom和sendto
 * 4. 关闭套接字close
 * 
 * ssize_t sendto (int __fd, const void *__buf, size_t __n, int __flags, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len);    
 * //发送数据，并且指定发送数据的客户端地址信息
 * 
 * ssize_t recvfrom (int __fd, void * __buf, size_t __n, int __flags,  __SOCKADDR_ARG __addr, socklen_t *__addr_len)
 * //接收数据，并且获取发送数据的客户端地址信息
 */

void server(const char *ip, int port)
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockFd == -1){
        perror("socket error");
        exit(1);
    }

    int pause = 1;
    int ret = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &pause, sizeof(pause));
    if(ret == -1){
        perror("setsockopt error");
        exit(1);
    }
    ret = bind(sockFd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(ret == -1){
        perror("bind error");
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    char buf[1024] = {0};
    recvfrom(sockFd, buf, sizeof(buf)-1, 0,
             (struct sockaddr *)&client_addr, &client_addr_len);
    printf("client: ip = %s, port = %d, buf = %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buf);
    sendto(sockFd, "Hello, UDP Client!", strlen("Hello, UDP Client!"), 0,
           (struct sockaddr *)&client_addr, client_addr_len);

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