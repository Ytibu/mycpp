#include "head.h"

// 将fd添加到epoll中，监听可读事件
int epollAdd(int epfd, int fd)
{
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = fd;
    return epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
}

// 从epoll中删除fd
int epollDel(int epfd, int fd)
{
    return epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
}