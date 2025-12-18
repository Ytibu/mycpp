#include "Acceptor.h"
#include <stdio.h>


//创建Acceptor对象（由socket类创建socket，由InetAddress类创建地址和端口）
Acceptor::Acceptor(const string& ip, unsigned short port)
: _sock()
, _addr(ip, port)
{
}

Acceptor::~Acceptor()
{
}

// 对外接口：启动监听
void Acceptor::ready()
{
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

// 地址复用
void Acceptor::setReuseAddr()
{
    int optval = 1;
    int ret = ::setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (ret < 0)
    {
        perror("setsockopt");
    }
}

// 端口复用
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


// 绑定
void Acceptor::bind()
{
    int ret = ::bind(_sock.fd(), (struct sockaddr *)_addr.getSockAddr(), sizeof(struct sockaddr));
    if (ret < 0)
    {
        perror("bind");
        return;
    }
}

// 监听
void Acceptor::listen()
{
    int ret = ::listen(_sock.fd(), 128);
    if (ret < 0)
    {
        perror("listen");
        return;
    }
}

// 接受连接
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

// 获取fd(由Socket类提供)
int Acceptor::fd() const
{
    return _sock.fd();
}
