#include "ThreadPool.h"
#include "WorkThread.h"
#include "Task.h"
// #include "TaskQueue.h"

#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize) :
 _threadNum(threadNum),
 _queSize(queSize),
 _taskQue(_queSize),
 _isExit(false)
{
    _threads.reserve(_threadNum);   // 工作线程容器 预留空间 ：threadNum
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::start()
{
    // 创建工作线程，运行工作线程
    for (size_t idx = 0; idx != _threadNum; ++idx)
    {
        // unique_ptr<Thread> up(new WorkThread(*this));
        // _threads.push_back(move(up));
        _threads.push_back(unique_ptr<Thread>(new WorkThread(*this)));
        //将工作线程加入到线程池中
    }
    for (auto &th : _threads)
    {
        th->start();
    }
}

void ThreadPool::stop()
{
    //任务在不执行完毕的情况下，不让子线程推出
    while(!_taskQue.empty()){
        sleep(1);
    }
    _isExit = true;
    
    _taskQue.wakeup();  //回收资源之前唤醒所有线程

    //回收所有线程资源
    for (auto &th : _threads)   
    {
        th->stop();
    }
}

void ThreadPool::addTask(Task *ptask)
{
    if (ptask)
    {
        _taskQue.push(ptask);
    }
}
Task *ThreadPool::getTask()
{
    return _taskQue.pop();
}

void ThreadPool::doTask()
{
    //使用线程池是否退出的标志位
    while (!_isExit)
    {
        Task *ptask = getTask();
        if (ptask)
        {
            ptask->process();   //执行任务
        }
        else
        {
            cout << "ptask is nullptr" << endl;
        }
    }
}
