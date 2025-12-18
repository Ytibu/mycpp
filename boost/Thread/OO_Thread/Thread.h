#ifndef __THREAD_H__
#define __THREAD_H__
#include <pthread.h>

class Thread
{
public:
    Thread();
    virtual ~Thread();
    //线程启动
    void start();
    //线程停止
    void stop();
private:
    //线程入口函数
    static void *threadFunc(void *arg);
    //线程任务
    virtual void run() = 0;
private:
    pthread_t _thid;  //线程id
    bool _isRuning; //线程是否运行的标志

};

#endif