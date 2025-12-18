#include "TimerFd.h"
#include <unistd.h>
#include <sys/timerfd.h>
#include <poll.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>


using std::cout;
using std::endl;


//使用 Linux 内核提供的 TimerFd 创建事件描述符，支持事件的等待、唤醒和处理


TimerFd::TimerFd(TimerFdCallback &&cb, int initSec, int peridocSec)
: _tfd(createTimerFd())
, _cb(std::move(cb))
, _isStarted(false)
, _initSec(initSec)
, _peridocSec(peridocSec)
{

}

TimerFd::~TimerFd(){
    setTimer(0, 0);
    close(_tfd);
}

//启动事件监听循环，使用 poll 等待事件
void TimerFd::start(){

    struct pollfd pfd;
    pfd.fd = _tfd;
    pfd.events = POLLIN;

    setTimer(_initSec, _peridocSec);

    _isStarted = true;  //监听开始
    //循环监听
    while(_isStarted)
    {
        int nready = poll(&pfd, 1, 3000);
        if(nready == -1 && errno == EINTR){
            continue;
        }else if(nready == -1){
            perror("poll");
            break;
        }else if(nready == 0){
            cout << "timeout" << endl;
            continue;
        }else
        {
            if(pfd.revents & POLLIN){
                handleRead();
                if(_cb){
                    _cb();
                }
            }
        }

    }

}

// 停止事件监听
void TimerFd::stop(){
    _isStarted = false; //监听停止
    setTimer(0, 0);
}



// 处理事件读取
void TimerFd::handleRead()   
{
    uint64_t two;
    ssize_t ret = read(_tfd, &two, sizeof(uint64_t));
    if(ret != sizeof(uint64_t)){
        perror("read");
        return;
    }
}

// 创建文件描述符
int TimerFd::createTimerFd() 
{
    int fd = timerfd_create(CLOCK_REALTIME, 0);
    if(fd < 0){
        perror("timerfd_create");
        return -1;
    }
    return fd;
}

// 设置定时器
void TimerFd::setTimer(int initSec, int peridocSec)
{
    struct itimerspec value;
    value.it_value.tv_sec = initSec;
    value.it_value.tv_nsec = 0;
    value.it_interval.tv_sec = peridocSec;
    value.it_interval.tv_nsec = 0;
    int ret = timerfd_settime(_tfd, 0, &value, nullptr);
}