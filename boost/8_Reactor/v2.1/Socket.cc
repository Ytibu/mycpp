#include "Socket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

Socket::Socket(){
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    if(_fd < 0){
        perror("socket");
    }
}
Socket::Socket(int fd): _fd(fd)
{
}

Socket::~Socket(){
    if(_fd >= 0){
        close(_fd);
    }
}

int Socket::fd() const{
    return _fd;
}

void Socket::shutDownWrite(){
    int ret = shutdown(_fd, SHUT_WR);
    if(ret < 0){
        perror("shutdown");
        return;
    }
}