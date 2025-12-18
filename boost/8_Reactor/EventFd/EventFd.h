#ifndef __EVENTFD_H__
#define __EVENTFD_H__ 

#include <functional>


//该文件实现了 EventFd 类，这是一个基于 Linux eventfd 机制的事件通知器，用于线程间通信和事件唤醒。


class EventFd {
    using EventFdCallback = std::function<void()>;
public:
    EventFd(EventFdCallback &&cb);
    ~EventFd();

    // 启动
    void start();

    // 停止
    void stop();

    void wakeup();  //唤醒
    void handleRead();  //处理事件
    int createEventFd();    //创建文件描述符

private:
    int _evtfd; //产生的文件描述符
    EventFdCallback _cb;    //执行任务
    bool _isStarted;    //标识符
};

#endif