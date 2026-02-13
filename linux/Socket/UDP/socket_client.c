#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/**
 * UDP客户端
 * 1. 创建套接字socket
 * 2. 进行通信recvfrom和sendto
 * 3. 关闭套接字close
 * 
 * ssize_t sendto (int __fd, const void *__buf, size_t __n, int __flags, __CONST_SOCKADDR_ARG __addr, socklen_t __addr_len);    
 * //发送数据，并且指定发送数据的服务器地址信息
 * 
 * ssize_t recvfrom (int __fd, void * __buf, size_t __n, int __flags,  __SOCKADDR_ARG __addr, socklen_t *__addr_len)
 * //接收数据，并且获取发送数据的服务器地址信息
 */

void client(const char *ip, int port)
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockFd < 0){
        perror("socket error");
        exit(1);
    }

    sendto(sockFd, "Hello, UDP Server!", strlen("Hello, UDP Server!"), 0,
           (struct sockaddr *)&server_addr, sizeof(server_addr));

    char buf[1024] = {0};
    recvfrom(sockFd, buf, sizeof(buf)-1, 0, NULL, NULL);
    printf("Received from server: %s\n", buf);


    close(sockFd);
}


int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("argc error\n");
        return -1;
    }

    client(argv[1], atoi(argv[2]));

    return 0;
}