#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__ 

#include <vector>
#include <map>
#include <memory>
#include <functional>

#include "TcpConnection.h"
#include "Acceptor.h"



//EventLoop类：封装epoll，实现epoll的三个函数使用，同时实现循环下的epoll的传输与读写


// 前置声明
class TcpConnection;
class Acceptor;


class EventLoop{
    using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
    using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &)>;    // 创建连接的回调函数

public:
    EventLoop(Acceptor &acceptor);
    ~EventLoop();

    void loop();    // 启动事件循环
    void unloop();  // 退出事件循环

    void waitEpollFd(); // 等待epoll_wait

    void handNewConnection();   // 处理新连接
    void handMessage(int fd);   // 处理消息

    int createEpollFd();    // 创建epoll文件描述符
    void addEpollReadFd(int fd);    // 添加监听的文件描述符
    void delEpollReadFd(int fd);    // 删除指定的监听的文件描述符

    // 设置回调函数注册
    void setNewConnectionCallback(TcpConnectionCallback &&cb);
    void setMessageCallback(TcpConnectionCallback &&cb);
    void setCloseCallback(TcpConnectionCallback &&cb);

private:
    int _epfd;  // epoll fd
    Acceptor &_acceptor;
    std::vector<struct epoll_event> _evtList;
    bool _isLooping;
    std::map<int, TcpConnectionPtr> _conns;

    TcpConnectionCallback _onNewConnectionCb;   //建立连接
    TcpConnectionCallback _onCloseCb;       //连接断开
    TcpConnectionCallback _onMessageCb;     //消息到达
};

#endif