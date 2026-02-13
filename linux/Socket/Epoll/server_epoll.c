#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

/**
 * int epoll_create (int __size)    //创建一个epoll对象，返回epoll的文件描述符
 * int epoll_ctl (int __epfd, int __op, int __fd, struct epoll_event *__event)  //控制epoll对象的行为
 *     op:   EPOLL_CTL_ADD: 添加一个文件描述符到epoll对象中
 *           EPOLL_CTL_MOD: 修改已经添加到epoll对象中的文件描述符
 *           EPOLL_CTL_DEL: 从epoll对象中删除一个文件描述符
 *
 *  struct epoll_event {
 *     uint32_t events;    //感兴趣的事件
 *     epoll_data_t data;  //用户数据
 * };
 * typedef union epoll_data {
 *     void *ptr;
 *     int fd;
 *    uint32_t u32;
 *    uint64_t u64;
 * } epoll_data_t;
 *
 * int epoll_wait (int __epfd, struct epoll_event *__events, int __maxevents, int __timeout)  //等待事件的发生
 *    __events: 用于存储发生事件的数组; __maxevents: 数组的大小; __timeout: 等待事件发生的超时时间
 *
 */

void server(char *ip, int port)
{
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    int pause = 1;
    int ret = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &pause, sizeof(pause));
    ret = bind(sockFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    ret = listen(sockFd, 128);
    int netFd = accept(sockFd, NULL, NULL);

    int epfd = epoll_create(1);
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    event.events = EPOLLIN;
    event.data.fd = netFd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, netFd, &event);

    char buffer[1024] = {0};
    while (1)
    {
        struct epoll_event readySet[2];
        int readyNum = epoll_wait(epfd, readySet, 2, -1);
        for (int i = 0; i < readyNum; ++i)
        {
            if (readySet[i].data.fd == STDIN_FILENO)
            {
                memset(buffer, 0, sizeof(buffer));
                read(STDIN_FILENO, buffer, sizeof(buffer));
                send(netFd, buffer, strlen(buffer), 0);
            }
            else if (readySet[i].data.fd == netFd)
            {
                memset(buffer, 0, sizeof(buffer));
                int len = recv(netFd, buffer, sizeof(buffer), 0);
                if (len > 0)
                {
                    printf("recv: %s", buffer);
                }
                else if (len == 0)
                {
                    printf("client closed\n");
                    close(netFd);
                    return;
                }
                else
                {
                    perror("recv error");
                    close(netFd);
                    return;
                }
            }
        }
    }
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