#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <time.h>

/* socket编程实现 即时通信的聊天室 */

typedef struct ClientInfo
{
    int isConnected;       // 是否连接
    int netFd;             // 客户端套接字
    time_t lastActiveTime; // 上次活跃时间
} Client_t;

// 通过将sockfd和acceptedFd加入不同的集合，将断线后的连接仍然保存，上线后继续通信
void Server(const char *ip, int port)
{
    // 设置地址结构体，创建套接字，绑定地址，监听连接请求
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
    int reuse = 1;
    int ret = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)); // 设置地址复用
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
    char buf[1024] = {0};

    // 初始化客户端连接数组和套接字索引数组
    Client_t clients[1024];
    for (int i = 0; i < 1024; ++i)
    {
        clients[i].netFd = -1; // 初始化连接套接字数组，表示没有客户端连接
    }
    int fdToIdx[1024]; // 用于记录套接字对应的索引，方便断线后重新加入监视集合
    for (int i = 0; i < 1024; ++i)
    {
        fdToIdx[i] = -1; // 初始化套接字索引数组，表示没有对应的连接套接字
    }
    int curIdx = 0; // 当前连接套接字数组的索引

    time_t now;
    while (1)
    {
        // 将监视集合复制到就绪集合中，select会修改就绪集合，所以每次都要重新复制
        memcpy(&readySet, &monitorSet, sizeof(fd_set));

        struct timeval timeout;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        ret = select(1024, &readySet, NULL, NULL, &timeout);
        if (ret < 0)
        {
            perror("select error");
            exit(1);
        }
        now = time(NULL);
        printf("TIME: now is %s\n", ctime(&now));

        // sockFd就绪后，阻塞等待新的连接请求，接受连接并将新的连接套接字加入监视集合中
        if (FD_ISSET(sockFd, &readySet))
        {
            // 有新的连接请求，接受连接并将新的连接套接字加入监视集合中
            clients[curIdx].netFd = accept(sockFd, NULL, NULL);
            if (clients[curIdx].netFd < 0)
            {
                perror("accept error");
                continue;
            }
            clients[curIdx].isConnected = 1;             // 标记为已连接
            clients[curIdx].lastActiveTime = time(NULL); // 记录当前时间

            printf("client %d connected, fd: %d, time: %s\n", curIdx, clients[curIdx].netFd, ctime(&clients[curIdx].lastActiveTime));

            fdToIdx[clients[curIdx].netFd] = curIdx;    // 记录套接字对应的索引
            FD_SET(clients[curIdx].netFd, &monitorSet); // 将新的连接套接字加入就绪集合中，等待客户端发送数据
            ++curIdx;                                   // 更新当前连接套接字数组的索引
        }

        // 遍历连接套接字数组，检查每个连接套接字是否就绪，如果就绪则接收数据并将数据转发给其他客户端
        for (int i = 0; i < curIdx; ++i)
        {
            if (clients[i].isConnected == 1 && FD_ISSET(clients[i].netFd, &readySet))
            {
                memset(buf, 0, sizeof(buf));
                int recv_ret = recv(clients[i].netFd, buf, sizeof(buf), 0);
                if (recv_ret <= 0)
                {
                    // 客户端断开连接，关闭套接字并从监视集合中移除
                    FD_CLR(clients[i].netFd, &monitorSet);
                    close(clients[i].netFd);
                    clients[i].netFd = -1;
                    clients[i].isConnected = 0;
                    printf("client disconnected, id: %d fd: %d\n", i, clients[i].netFd);
                    continue;
                }
                clients[i].lastActiveTime = time(NULL);
                printf("recv from client %d: %s\n", i, buf);
                for (int j = 0; j < curIdx; ++j)
                {
                    if (clients[j].isConnected == 1 && j != i)
                    {
                        send(clients[j].netFd, buf, strlen(buf), 0);
                    }
                }
            }
        }

        // 遍历连接套接字数组，检查每个连接套接字的活跃时间，如果超过10秒没有活跃，则认为断线，关闭套接字并从监视集合中移除
        for (int i = 0; i < curIdx; ++i)
        {
            if (clients[i].isConnected == 1 && now - clients[i].lastActiveTime > 10)
            {
                // 客户端超过10秒没有活跃，认为断线，关闭套接字并从监视集合中移除
                FD_CLR(clients[i].netFd, &monitorSet);
                close(clients[i].netFd);
                clients[i].netFd = -1;
                clients[i].isConnected = 0;
                printf("client timeout, id: %d fd: %d\n", i, clients[i].netFd);
            }
        }
    }
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