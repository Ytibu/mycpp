#include "Thread.h"
#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace std;

Thread::Thread():_thid(0),_isRuning(false)
{
    
}

Thread::~Thread()
{
    
}

    
void Thread::start()
{   //线程启动
    int ret = pthread_create(&_thid,nullptr,threadFunc,this);
    if(ret){
        perror("pthread_create");
        return;
    }
    _isRuning = true;
}
    
void Thread::stop()
{   //线程停止
    if(_isRuning){
        int ret = pthread_join(_thid, nullptr);
        if(ret){
            perror("pthread_join");
            return;
        }
        _isRuning = false;
    }
    
}

    
void *Thread::threadFunc(void *arg)
{   //线程入口函数
    Thread *p = static_cast<Thread *>(arg);
    if(p){
        p->run();
    }else{
        cout<<"nullptr == p"<<endl;
    }
    return nullptr;
}
    
void Thread::run()
{   //线程任务

}
