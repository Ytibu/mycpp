#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

/**
 * 利用epoll实现一个支持断线重连的单客户端服务器
 * 1. 服务器监听一个端口，等待客户端连接
 * 2. 当客户端连接后，服务器开始监听该客户端的消息和标准输入
 * 3. 如果客户端断开连接，服务器停止监听该客户端，并重新监听端口等待新的连接
 * 4. 如果标准输入有数据，服务器将数据发送给当前连接的客户端
 * 5. 服务器能够处理客户端的断线重连，确保在客户端断开后能够接受新的连接并继续通信
 */

void server(char *ip, int port)
{
    /* 初始化服务端监听地址 */
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    /* 创建监听 socket，并设置地址复用 */
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    int pause = 1;
    setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &pause, sizeof(pause));
    bind(sockFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(sockFd, 128);

    /* 当前唯一客户端连接及其信息 */
    int netFd = -1;
    struct sockaddr_in currentClientAddr;
    memset(&currentClientAddr, 0, sizeof(currentClientAddr));
    char currentClientIp[INET_ADDRSTRLEN] = {0};
    unsigned short currentClientPort = 0;

    char buffer[1024] = {0};

    /* 监听sockfd */
    int epFd = epoll_create(1);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = sockFd;
    epoll_ctl(epFd, EPOLL_CTL_ADD, sockFd, &event);
    while (1)
    {
        /* 等待事件触发 */
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        struct epoll_event readySet[1024];
        int readyNum = epoll_wait(epFd, readySet, 1024, -1);
        for (int i = 0; i < readyNum; ++i)
        {

            // 发现sockFd就绪后，开始监听netFd和STDIN_FILENO
            if (readySet[i].data.fd == sockFd)
            {
                netFd = accept(sockFd, (struct sockaddr *)&clientAddr, &clientAddrLen);
                if (netFd < 0)
                {
                    perror("accept error");
                    continue;
                }

                char newClientIp[INET_ADDRSTRLEN] = {0};
                inet_ntop(AF_INET, &clientAddr.sin_addr, newClientIp, sizeof(newClientIp));
                strcpy(currentClientIp, newClientIp);
                currentClientPort = ntohs(clientAddr.sin_port);
                printf("client connected: ip=%s, port=%u\n", newClientIp, ntohs(clientAddr.sin_port));

                epoll_ctl(epFd, EPOLL_CTL_DEL, sockFd, NULL);

                event.events = EPOLLIN;
                event.data.fd = netFd;
                epoll_ctl(epFd, EPOLL_CTL_ADD, netFd, &event);

                event.events = EPOLLIN;
                event.data.fd = STDIN_FILENO;
                epoll_ctl(epFd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
            }
            /* 确保已经开始监听客户端并处理客户端消息 */
            else if (netFd != -1 && readySet[i].data.fd == netFd)
            {
                memset(buffer, 0, sizeof(buffer));
                int recv_len = recv(netFd, buffer, sizeof(buffer), 0);
                if (recv_len < 0)
                {
                    perror("recv error");
                    /* 发生错误，清理当前客户端连接 */
                    epoll_ctl(epFd, EPOLL_CTL_DEL, netFd, NULL);
                    close(netFd);
                    netFd = -1;
                }
                else if (recv_len == 0)
                {
                    /* 清理当前客户端连接 */
                    event.events = EPOLLIN;
                    event.data.fd = sockFd;
                    epoll_ctl(epFd, EPOLL_CTL_ADD, sockFd, &event);     // 重新监听sockFd
                    epoll_ctl(epFd, EPOLL_CTL_DEL, netFd, NULL);        // 停止监听netFd
                    epoll_ctl(epFd, EPOLL_CTL_DEL, STDIN_FILENO, NULL); // 停止监听STDIN_FILENO
                    close(netFd);
                    netFd = -1;
                    printf("client closed: ip=%s, port=%u\n", currentClientIp, currentClientPort);
                    break;
                }
                else
                {
                    printf("recv from ip=%s, port=%u: %.*s", currentClientIp, currentClientPort, recv_len, buffer);
                }
            }
            else if (netFd != -1 && readySet[i].data.fd == STDIN_FILENO)
            {
                memset(buffer, 0, sizeof(buffer));
                ssize_t read_len = read(STDIN_FILENO, buffer, sizeof(buffer));
                if (read_len < 0)
                {
                    perror("read stdin error");
                    continue;
                }
                else if (read_len == 0)
                {
                    event.events = EPOLLIN;
                    event.data.fd = sockFd;
                    epoll_ctl(epFd, EPOLL_CTL_ADD, sockFd, &event);     // 重新监听sockFd
                    epoll_ctl(epFd, EPOLL_CTL_DEL, netFd, NULL);        // 停止监听netFd
                    epoll_ctl(epFd, EPOLL_CTL_DEL, STDIN_FILENO, NULL); // 停止监听STDIN_FILENO
                    close(netFd);
                    netFd = -1;
                    printf("stdin closed\n");
                    break;
                }
                else
                {
                    /* 已有客户端：直接发送当前输入 */
                    send(netFd, buffer, read_len, 0);
                }
            }
        }
    }
    close(epFd);
    close(netFd);
    close(sockFd);
}
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("argc error\n");
        return 1;
    }
    server(argv[1], atoi(argv[2]));
}