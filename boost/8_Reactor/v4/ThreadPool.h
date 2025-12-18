#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__ 

#include <vector>
#include <memory>
#include <functional>

//#include "Thread.h"
#include "TaskQueue.h"
using std::vector;
using std::unique_ptr;
using std::function;
using std::bind;

class Thread;
using  Task = function<void()>;

class ThreadPool
{
    friend class WorkThread;    //workThread访问ThreadPool的私有成员doTask
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();   //启动线程池
    void stop();    //停止线程池
    void addTask(Task &&task);  //添加任务
private:
    Task getTask();    //获取任务
    void doTask();  //执行任务

private:
    size_t _threadNum;  //线程数量
    size_t _queSize;    //任务队列最大容量
    vector<unique_ptr<Thread>> _threads;    //工作线程容器
    TaskQueue _taskQue; //任务容器
    bool _isExit;   //是否结束

};

#endif