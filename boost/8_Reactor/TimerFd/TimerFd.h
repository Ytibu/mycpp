#ifndef __TIMERFD_H__
#define __TIMERFD_H__ 

#include <functional>


//该文件实现了 TimerFd 类，这是一个基于 Linux TimerFd 机制的事件通知器，用于线程间通信和事件唤醒。


class TimerFd {
    using TimerFdCallback = std::function<void()>;
public:
    TimerFd(TimerFdCallback &&cb, int initSec, int peridoSec);
    ~TimerFd();
    // 启动
    void start();
    // 停止
    void stop();

private:
    void handleRead();  //处理事件
    int createTimerFd();    //创建文件描述符
    void setTimer(int initSec, int peridoSec);

private:
    int _tfd; //产生的文件描述符
    TimerFdCallback _cb;    //执行任务
    bool _isStarted;    //标识符
    int _initSec;   //起始时间
    int _peridocSec;    //间隔时间
};

#endif