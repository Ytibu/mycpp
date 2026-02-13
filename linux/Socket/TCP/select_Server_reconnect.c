#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

/**
 * 服务端
 * 1. select + socket 实现服务端与客户端即时通信
 * 2. 实现服务端支持断线重连，客户端断开连接后，服务端继续监听，等待客户端重新连接
 */


//通过将sockfd和acceptedFd加入不同的集合，将断线后的连接仍然保存，上线后继续通信
void Server(const char *ip, int port)
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        perror("socket error");
        exit(1);
    }

    // 设置地址复用
    int reuse = 1;
    int ret = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (ret < 0)
    {
        perror("setsockopt error");
        exit(1);
    }
    ret = bind(sockFd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0)
    {
        perror("bind error");
        exit(1);
    }

    ret = listen(sockFd, 50);
    if (ret < 0)
    {
        perror("listen error");
        exit(1);
    }

    // 初始化监视集合和就绪集合，并将监听套接字加入监视集合中
    fd_set monitorSet, readySet;
    FD_ZERO(&monitorSet);
    FD_SET(sockFd, &monitorSet);

    int maxFd = sockFd;
    char buf[1024] = {0};

    int netFd = -1; // 初始化连接套接字为-1，表示没有客户端连接
    while (1)
    {
        // 将监视集合复制到就绪集合中，select会修改就绪集合，所以每次都要重新复制
        memcpy(&readySet, &monitorSet, sizeof(monitorSet));
        int ret = select(20, &readySet, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select error");
            exit(1);
        }

        if (FD_ISSET(sockFd, &readySet))
        {
            // 有新的连接请求，接受连接
            netFd = accept(sockFd, NULL, NULL);
            if (netFd < 0)
            {
                perror("accept error");
                continue;
            }

            FD_CLR(sockFd, &monitorSet);       // 清除监听套接字的就绪状态，继续监视新的连接请求
            FD_SET(STDIN_FILENO, &monitorSet); // 将标准输入加入就绪集合中，等待用户输入数据
            FD_SET(netFd, &monitorSet);        // 将新的连接套接字加入就绪集合中，等待客户端发送数据
        }

        if ( netFd != -1 && FD_ISSET(netFd, &readySet))
        {
            memset(buf, 0, sizeof(buf));
            int recv_len = recv(netFd, buf, sizeof(buf), 0);
            if (recv_len < 0)
            {
                perror("recv error");
                continue;
            }
            else if (recv_len == 0)
            {
                FD_SET(sockFd, &monitorSet);       // 重新将监听套接字加入监视集合中，等待新的连接请求
                FD_CLR(STDIN_FILENO, &monitorSet); // 将标准输入从监视集合中移除，停止等待用户输入数据
                FD_CLR(netFd, &monitorSet);        // 将断开连接的套接字从监视集合中移除
                close(netFd);
                netFd = -1; // 重置连接套接字为-1，表示没有客户端连接
                printf("client disconnected\n");
                continue;
            }
            else
            {
                printf("recv from client: %s", buf);
            }
        }
        if (FD_ISSET(STDIN_FILENO, &readySet))
        {
            memset(buf, 0, sizeof(buf));
            int read_len = read(STDIN_FILENO, buf, sizeof(buf));
            if (read_len < 0)
            {
                perror("read error");
                break;
            }
            else if (read_len == 0)
            {
                FD_SET(sockFd, &monitorSet);       // 重新将监听套接字加入监视集合中，等待新的连接请求
                FD_CLR(STDIN_FILENO, &monitorSet); // 将标准输入从监视集合中移除，停止等待用户输入数据
                FD_CLR(netFd, &monitorSet);        // 将断开连接的套接字从监视集合中移除
                close(netFd);
                netFd = -1; // 重置连接套接字为-1，表示没有客户端连接
                printf("client disconnected\n");
                continue;
            }
            else
            {
                send(netFd, buf, read_len, 0);
            }
        }
    }
    close(netFd);
    close(sockFd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("argc error\n");
        exit(1);
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    Server(ip, port);

    return 0;
}