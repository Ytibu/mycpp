#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <time.h>

/**
 * 利用epoll实现聊天室服务器
 * 1. 创建socket，绑定地址，监听端口
 * 2. 创建epoll对象，将监听socket添加到epoll中
 * 3. 循环等待事件发生，处理事件
 *    1. 如果是监听socket，接受连接，将新连接添加到epoll中
 *    2. 如果是客户端socket，接收数据，转发给其他在线客户端，如果接收数据失败，关闭连接，从epoll中删除
 * 4. 定期检查在线客户端的最后活跃时间，超过一定时间未活跃的客户端，关闭连接，从epoll中删除
 */

typedef struct
{
    int isOnline;
    int netFd;
    time_t lastActiveTime;
} ClientInfo;

void server(char *ip, int port)
{
    // 1) 初始化服务器地址
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    // 2) 创建监听socket并开始监听
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    int pause = 1;
    int ret = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &pause, sizeof(pause));
    ret = bind(sockFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    ret = listen(sockFd, 5);

    // 3) 创建epoll对象并注册监听socket
    int epFd = epoll_create(1);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = sockFd;
    ret = epoll_ctl(epFd, EPOLL_CTL_ADD, sockFd, &event);

    // 4) 初始化客户端状态表与fd到索引映射
    ClientInfo clients[1024];
    for (int i = 0; i < 1024; i++)
    {
        clients[i].isOnline = 0;
        clients[i].netFd = -1;
        clients[i].lastActiveTime = 0;
    }
    int fdToidx[1024];
    for (int i = 0; i < 1024; i++)
    {
        fdToidx[i] = -1;
    }
    int curIdx = 0;
    char buf[1024] = {0};
    time_t now;
    // 5) 事件循环：处理连接、读事件、以及超时清理
    while (1)
    {
        struct epoll_event readySet[1024];
        int readyNum = epoll_wait(epFd, readySet, 1024, 10);
        now = time(NULL);
        // printf("now Time:%ld\n", now);
        for (int i = 0; i < readyNum; ++i)
        {
            if (readySet[i].data.fd == sockFd)
            {
                // 5.1) 有新连接到来，accept并加入epoll
                struct sockaddr_in clientAddr;
                socklen_t len = sizeof(clientAddr);
                int clientFd = accept(sockFd, (struct sockaddr *)&clientAddr, &len);
                printf("client:%d %s:%d connected\n", clientFd, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

                clients[curIdx].isOnline = 1;
                clients[curIdx].netFd = clientFd;
                clients[curIdx].lastActiveTime = time(NULL);
                fdToidx[clientFd] = curIdx;

                event.events = EPOLLIN;
                event.data.fd = clientFd;
                ret = epoll_ctl(epFd, EPOLL_CTL_ADD, clientFd, &event);

                ++curIdx;
            }
            else
            {
                // 5.2) 客户端可读事件：接收并广播
                int clientFd = readySet[i].data.fd;
                memset(buf, 0, sizeof(buf));
                int recv_len = recv(clientFd, buf, sizeof(buf), 0);
                if (recv_len < 0)
                {
                    perror("recv error");
                    continue;
                }
                else if (recv_len == 0)
                {
                    // 5.2.1) 客户端主动断开，清理资源
                    int idx = fdToidx[clientFd];
                    clients[idx].isOnline = 0;
                    clients[idx].netFd = -1;
                    clients[idx].lastActiveTime = 0;
                    fdToidx[clientFd] = -1;

                    epoll_ctl(epFd, EPOLL_CTL_DEL, clientFd, NULL);

                    struct sockaddr_in clientAddr;
                    socklen_t len = sizeof(clientAddr);
                    getpeername(clientFd, (struct sockaddr *)&clientAddr, &len);
                    printf("client:%d %s:%d disconnected\n", clientFd, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

                    close(clientFd);

                    continue;
                }

                int idx = fdToidx[clientFd];
                clients[idx].lastActiveTime = time(NULL);
                printf("recv from client:%d, msg:%s", clientFd, buf);

                for (int j = 0; j < curIdx; ++j)
                {
                    if (clients[j].isOnline == 1 && clients[j].netFd != clientFd)
                    {
                        send(clients[j].netFd, buf, recv_len, 0);
                    }
                }
            }
        }

        // 5.3) 定期超时检查：清理长时间未活跃连接
        for (int i = 0; i < curIdx; ++i)
        {
            if (now - clients[i].lastActiveTime > 10 && clients[i].isOnline == 1)
            {
                // 超过60秒未活跃，关闭连接
                int clientFd = clients[i].netFd;

                clients[i].isOnline = 0;
                clients[i].netFd = -1;
                fdToidx[clientFd] = -1;

                epoll_ctl(epFd, EPOLL_CTL_DEL, clientFd, NULL);
                close(clientFd);

                struct sockaddr_in clientAddr;
                socklen_t len = sizeof(clientAddr);
                getpeername(clientFd, (struct sockaddr *)&clientAddr, &len);
                printf("client:%d %s:%d timed out\n", clientFd, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
            }
        }
    }

    close(sockFd);
    close(epFd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("argc error\n");
        return 1;
    }

    server(argv[1], atoi(argv[2]));

    return 0;
}