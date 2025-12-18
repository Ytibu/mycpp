#include "EventFd.h"

#include <unistd.h>
#include <sys/eventfd.h>
#include <poll.h>
#include <errno.h>
#include <stdio.h>

#include <iostream>


using std::cout;
using std::endl;


//使用 Linux 内核提供的 eventfd 创建事件描述符，支持事件的等待、唤醒和处理


EventFd::EventFd(EventFdCallback &&cb)
: _evtfd(createEventFd())
, _cb(std::move(cb))
, _isStarted(false)
{

}

EventFd::~EventFd(){
    close(_evtfd);
}

//启动事件监听循环，使用 poll 等待事件
void EventFd::start(){

    struct pollfd pfd;
    pfd.fd = _evtfd;
    pfd.events = POLLIN;

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
void EventFd::stop(){
    _isStarted = false; //监听停止
}

// 唤醒事件监听器
void EventFd::wakeup()       
{
    uint64_t one = 1;
    ssize_t ret = write(_evtfd, &one, sizeof(uint64_t));
    if(ret != sizeof(uint64_t)){
        perror("write");
        return;
    }
}

// 处理事件读取
void EventFd::handleRead()   
{
    uint64_t two;
    ssize_t ret = read(_evtfd, &two, sizeof(uint64_t));
    if(ret != sizeof(uint64_t)){
        perror("read");
        return;
    }
}

// 创建文件描述符
int EventFd::createEventFd() 
{
    int fd = eventfd(10, EFD_NONBLOCK | EFD_CLOEXEC);
    if(fd < 0){
        perror("eventfd");
        return -1;
    }
    return fd;
}