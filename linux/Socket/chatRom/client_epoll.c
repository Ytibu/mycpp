#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

enum
{
    MAX_BUF = 1024
};

void client(char *ip, int port)
{
    // 定义服务器地址
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    // 创建socket并连接服务器
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        perror("socket");
        return;
    }
    int ret = connect(sockFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        perror("connect");
        close(sockFd);
        return;
    }

    // 创建epoll并监听stdin和socket
    int epFd = epoll_create(1);
    if (epFd < 0)
    {
        perror("epoll_create");
        close(sockFd);
        return;
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    ret = epoll_ctl(epFd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    if (ret < 0)
    {
        perror("epoll_ctl add stdin");
        close(epFd);
        close(sockFd);
        return;
    }

    event.events = EPOLLIN;
    event.data.fd = sockFd;
    ret = epoll_ctl(epFd, EPOLL_CTL_ADD, sockFd, &event);
    if (ret < 0)
    {
        perror("epoll_ctl add socket");
        close(epFd);
        close(sockFd);
        return;
    }

    char buffer[MAX_BUF] = {0};
    while (1)
    {
        struct epoll_event readySet[2];
        int readyNum = epoll_wait(epFd, readySet, 2, -1);
        if (readyNum < 0)
        {
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < readyNum; ++i)
        {
            if (readySet[i].data.fd == STDIN_FILENO)
            {
                // 从标准输入读取并发送
                ssize_t nread = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
                if (nread <= 0)
                {
                    // stdin关闭或出错，结束客户端
                    goto cleanup;
                }
                buffer[nread] = '\0';
                send(sockFd, buffer, nread, 0);
            }
            else if (readySet[i].data.fd == sockFd)
            {
                // 从服务器接收并输出
                ssize_t nrecv = recv(sockFd, buffer, sizeof(buffer) - 1, 0);
                if (nrecv <= 0)
                {
                    printf("server closed\n");
                    goto cleanup;
                }
                buffer[nrecv] = '\0';
                printf("%s", buffer);
                fflush(stdout);
            }
        }
    }

cleanup:
    close(epFd);
    close(sockFd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("usage: %s <ip> <port>\n", argv[0]);
        return 1;
    }

    client(argv[1], atoi(argv[2]));

    return 0;
}
