#include "Acceptor.h"
#include <stdio.h>


// Acceptor的初始化(ip和port交给InetAddress创建出地址结构体，socket创建出socket文件描述符(ipv4协议,Tcp协议，默认协议))
Acceptor::Acceptor(const string& ip, unsigned short port)
: _sock()
, _addr(ip, port)
{
}

Acceptor::~Acceptor()
{
}

//// 即：绑定，监听，设置地址端口复用(简化对外接口的代码量)
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

// 绑定地址
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

// 阻塞等待连接
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

// 获取fd
int Acceptor::fd() const
{
    return _sock.fd();  // _sock.fd()的创建由Socket类完成，
    //交由Socket类返回socket文件描述符
}
