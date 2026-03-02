#include <stdio.h>
#include <sys/epoll.h>

int epollAdd(int epfd, int fd);
int epollDel(int epfd, int fd);