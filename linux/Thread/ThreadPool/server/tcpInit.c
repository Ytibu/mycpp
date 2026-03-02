#include "tcpInit.h"

#include "errorSet.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


// 创建socketFd，绑定地址和端口，监听
int tcpInit(const  char *ip, const int port, int *pSockfd)
{

    *pSockfd = socket(AF_INET, SOCK_STREAM, 0);
    int reuse = 1;
    int ret = setsockopt(*pSockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    
    struct sockaddr_in serAddr;
    memset(&serAddr, 0, sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(port);
    serAddr.sin_addr.s_addr = inet_addr(ip);

    ret = bind(*pSockfd, (struct sockaddr *)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "bind");
    
    ret = listen(*pSockfd, 10);
    ERROR_CHECK(ret, -1, "listen");

    return 0;
}