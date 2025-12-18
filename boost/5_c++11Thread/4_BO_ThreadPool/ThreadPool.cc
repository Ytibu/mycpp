#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>
#include <memory>

using std::cout;
using std::endl;
using std::bind;
using std::thread;

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
        _threads.push_back(thread(&ThreadPool::doTask, this));
        //将工作线程加入到线程池中
    }
}

void ThreadPool::stop()
{
    //任务在不执行完毕的情况下，不让子线程推出
    while(!_taskQue.empty()){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    _isExit = true;
    
    _taskQue.wakeup();  //回收资源之前唤醒所有线程

    //回收所有线程资源
    for (auto &th : _threads)   
    {
        th.join();
    }
}

void ThreadPool::addTask(Task &&task)
{
    if (task)
    {
        _taskQue.push(std::move(task));
    }
}
Task ThreadPool::getTask()
{
    return _taskQue.pop();
}

void ThreadPool::doTask()
{
    //使用线程池是否退出的标志位
    while (!_isExit)
    {
        Task taskcb = getTask();
        if (taskcb)
        {
            taskcb();   //执行任务
        }
        else
        {
            cout << "ptask is nullptr" << endl;
        }
    }
}
