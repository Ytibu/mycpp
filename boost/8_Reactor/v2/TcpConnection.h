#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"
#include <memory>
#include <functional>

class TcpConnection;

// TcpConnection类，实现了TCP协议的读写功能
using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &)>;

class TcpConnection : public std::enable_shared_from_this<TcpConnection> {

public:
    explicit TcpConnection(int fd);
    ~TcpConnection();

    void send(const string &msg);
    string receive();
    bool isClosed() const;

    string toString();  //代码日志输出(打印本地和对端的ip和端口号)

    // 设置回调函数注册
    void setNewConnectionCallback(const TcpConnectionCallback &cb);
    void setMessageCallback(const TcpConnectionCallback &cb);
    void setCloseCallback(const TcpConnectionCallback &cb);
    
    //回调函数的运行
    void handleNewConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

private:
    //获取地址信息
    InetAddress getLocalAddress() ; // 获取本机地址信息
    InetAddress getPeerAddress() ;  // 获取对端地址信息

private:
    Socket _sock;   // socket套接字
    SocketIO _sockIO;

    InetAddress _localAddr; // 服务器地址
    InetAddress _peerAddr;  // 多个客户端的地址

    TcpConnectionCallback _onNewConnectionCb;   //建立连接
    TcpConnectionCallback _onCloseCb;       //连接断开
    TcpConnectionCallback _onMessageCb;     //消息到达
};

#endif