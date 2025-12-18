#include "Socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>


// 创建socket，生成socket文件描述符
Socket::Socket(){
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if(_fd < 0){
        perror("socket");
    }
}

// 传入的文件描述符作为socket文件描述符
Socket::Socket(int fd): _fd(fd)
{
}

// 关闭sokcet文件描述符
Socket::~Socket(){
    if(_fd >= 0){
        close(_fd);
    }
}

// 获取socket文件描述符
int Socket::fd() const{
    return _fd;
}


// 关闭socket文件描述符的写，仍然可以接收数据
void Socket::shutDownWrite(){
    int ret = shutdown(_fd, SHUT_WR);
    if(ret < 0){
        perror("shutdown");
        return;
    }
}