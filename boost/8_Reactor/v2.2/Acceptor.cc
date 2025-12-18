#include "Acceptor.h"
#include <stdio.h>


Acceptor::Acceptor(const string& ip, unsigned short port)
: _sock()
, _addr(ip, port)
{
}

Acceptor::~Acceptor()
{
}

void Acceptor::ready()
{
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}


void Acceptor::setReuseAddr()
{
    int optval = 1;
    int ret = ::setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (ret < 0)
    {
        perror("setsockopt");
    }
}


void Acceptor::setReusePort()
{
    int optval = 1;
    int ret = ::setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
    if (ret < 0)
    {
        perror("setsockopt");
        return;
    }
}



void Acceptor::bind()
{
    int ret = ::bind(_sock.fd(), (struct sockaddr *)_addr.getSockAddr(), sizeof(struct sockaddr));
    if (ret < 0)
    {
        perror("bind");
        return;
    }
}

void Acceptor::listen()
{
    int ret = ::listen(_sock.fd(), 128);
    if (ret < 0)
    {
        perror("listen");
        return;
    }
}


int Acceptor::accept()
{
    int connfd = ::accept(_sock.fd(), nullptr, nullptr);
    if (connfd < 0)
    {
        perror("accept");
        return -1;
    }
    return connfd;
}


int Acceptor::fd() const
{
    return _sock.fd();
}
