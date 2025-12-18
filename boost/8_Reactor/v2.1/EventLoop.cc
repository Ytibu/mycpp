#include "EventLoop.h"
#include "TcpConnection.h"

#include <unistd.h>
#include <sys/epoll.h>

#include <iostream>

// 构造函数
EventLoop::EventLoop(Acceptor &acceptor)
    : _epfd(createEpollFd()), _evtList(1024), _isLooping(false), _acceptor(acceptor)
{
    int listenfd = _acceptor.fd(); // 获取监听套接字
    addEpollReadFd(listenfd);      // 添加监听套接字到epoll中
}
EventLoop::~EventLoop()
{
    close(_epfd);
}

void EventLoop::loop()
{
    _isLooping = true;
    while (_isLooping)
    {
        waitEpollFd(); // 等待epoll_wait
    }
}
void EventLoop::unloop()
{
    _isLooping = false;
}

void EventLoop::waitEpollFd()
{

    int nready = 0;
    do
    {
        nready = epoll_wait(_epfd, &_evtList[0], _evtList.size(), 3000);
    } while (nready == -1 && errno == EINTR);

    if (nready == -1)
    {
        perror("waitEpollFd::epoll_wait");
        return;
    }
    else if (nready == 0)
    {
        std::cout << "time out" << std::endl;
    }
    else
    {
        if (nready == _evtList.size())
        {
            _evtList.resize(2 * nready);
        }
        for (int i = 0; i < nready; ++i)
        {
            int fd = _evtList[i].data.fd;
            if (fd == _acceptor.fd())
            {
                if (_evtList[i].events & EPOLLIN)
                    handNewConnection();
            }
            else
            {
                if (_evtList[i].events & EPOLLIN)
                    handMessage(fd);
            }
        }
    }
}


//处理新连接
void EventLoop::handNewConnection()
{
    int connfd = _acceptor.accept();
    if (connfd < 0)
    {
        perror("handNewConnection::accept");
        return;
    }

    addEpollReadFd(connfd);

    TcpConnectionPtr con(new TcpConnection(connfd));
    //回调函数的注册
    con->setNewConnectionCallback(std::move(_onNewConnectionCb));  //连接建立
    con->setMessageCallback(std::move(_onMessageCb));  //消息到达
    con->setCloseCallback(std::move(_onCloseCb));  //连接关闭

    _conns[connfd] = con;

    con->handleNewConnectionCallback(); //连接建立的回调
    
}


//消息处理
void EventLoop::handMessage(int fd)
{
    auto it = _conns.find(fd);
    if (it != _conns.end())
    {
        bool flag = it->second->isClosed();
        if(flag){
            it->second->handleCloseCallback();  //连接关闭的回调
            delEpollReadFd(fd); //删除epoll中的监听
            _conns.erase(it);   //删除连接
            
        }else{
            it->second->handleMessageCallback();    //消息到达的回调
        }
        
    }
    else
    {
        std::cout << "can not find fd:" << fd << std::endl;
        return;
    }
}


//创建epoll
int EventLoop::createEpollFd()
{

    return epoll_create(1024);
}
void EventLoop::addEpollReadFd(int fd)
{
    struct epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = fd;

    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &evt);
    if (ret < 0)
    {
        perror("addEpollReadFd::epoll_ctl");
        return;
    }
}
void EventLoop::delEpollReadFd(int fd)
{
}

void EventLoop::setNewConnectionCallback(TcpConnectionCallback &&cb){
    _onNewConnectionCb = std::move(cb);
}
void EventLoop::setMessageCallback(TcpConnectionCallback &&cb){
    _onMessageCb = std::move(cb);
}
void EventLoop::setCloseCallback(TcpConnectionCallback &&cb){
    _onCloseCb = std::move(cb);
}