#include "TcpConnection.h"

#include <iostream>
#include <sstream>
#include <sys/socket.h>

using std::cout;
using std::endl;
using std::ostringstream;


TcpConnection::TcpConnection(int fd)
    : _sockIO(fd), _sock(fd), _localAddr(getLocalAddress()), _peerAddr(getPeerAddress())
{
}

TcpConnection::~TcpConnection()
{
}

void TcpConnection::send(const string &msg)
{
    _sockIO.writen(msg.c_str(), msg.size());
}

string TcpConnection::receive()
{
    char buf[65535] = {0};
    _sockIO.readLine(buf, sizeof(buf));

    return string(buf);
}

bool TcpConnection::isClosed() const
{
    char buf[65535] = {0};
    int ret = recv(_sock.fd(), buf, sizeof(buf), MSG_PEEK);
    return (ret == 0);
}

string TcpConnection::toString()
{
    char buf[64];
    snprintf(buf, sizeof(buf), "%s:%d <-> %s:%d",
             _localAddr.ip().c_str(), _localAddr.port(),
             _peerAddr.ip().c_str(), _peerAddr.port());
    return buf;
}

// 获取本端的网络地址信息
InetAddress TcpConnection::getLocalAddress()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    // 获取本端地址的函数getsockname
    int ret = getsockname(_sock.fd(), (struct sockaddr *)&addr, &len);
    if (-1 == ret)
    {
        perror("getsockname");
    }

    return InetAddress(addr);
}

// 获取对端的网络地址信息
InetAddress TcpConnection::getPeerAddress()
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    // 获取对端地址的函数getpeername
    int ret = getpeername(_sock.fd(), (struct sockaddr *)&addr, &len);
    if (-1 == ret)
    {
        perror("getpeername");
    }

    return InetAddress(addr);
}

// 设置回调函数注册
void TcpConnection::setNewConnectionCallback( TcpConnectionCallback &&cb) {
    _onNewConnectionCb = std::move(cb);
}
void TcpConnection::setMessageCallback(TcpConnectionCallback &&cb) {
    _onMessageCb = std::move(cb);
}
void TcpConnection::setCloseCallback(TcpConnectionCallback &&cb) {
    _onCloseCb = std::move(cb);
}
// 回调函数的运行
void TcpConnection::handleNewConnectionCallback() {
    if(_onNewConnectionCb){
        //_onNewConnectionCb(std::shared_ptr<TcpConnection>(this));
        _onNewConnectionCb(shared_from_this());
    }else{
        cout << "_onNewConnectionCb is nullptr" << endl;
    }
}
void TcpConnection::handleMessageCallback() {
    if(_onMessageCb){
        _onMessageCb(shared_from_this());
    }else{
        cout << "_onMessageCb is nullptr" << endl;
    }
}
void TcpConnection::handleCloseCallback() {
    if(_onCloseCb){
        _onCloseCb(shared_from_this());
    }else{
        cout << "_onCloseCb is nullptr" << endl;
    }
}