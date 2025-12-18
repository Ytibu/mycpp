#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>

using std::queue;
using std::function;


using ElemType = function<void()>;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    //添加任务
    void  push(ElemType &&task);
    //获取任务
    ElemType pop();

    //任务队列是空与满
    bool full() const;
    bool empty() const;

    //所有等待在notEmpty条件上的线程唤醒
    void wakeup();

private:
    size_t _queSize;//任务队列的大小
    queue<ElemType> _que;//存放任务的数据结构
    MutexLock _mutex;//互斥锁
    Condition _notFull;//非满条件变量（生产者）
    Condition _notEmpty;//非空条件变量（消费者）
    bool _flag; //唤醒所有工作线程时，可以让while(true)结束

};

#endif
