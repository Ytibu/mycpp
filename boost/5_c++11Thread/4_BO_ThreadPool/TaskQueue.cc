#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notFull()
, _notEmpty()
, _flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

//添加任务
void TaskQueue::push(ElemType &&task)
{
    unique_lock<mutex> autoLock(_mutex);

    while(full())
    {
        //2.1、如果队列是满的，生产者需要睡眠
        _notFull.wait(autoLock);
    }
    //2.2、如果队列不为满才能进行push操作
    _que.push(std::move(task));
    //并且将消费者唤醒
    _notEmpty.notify_one();

}

//获取任务
ElemType TaskQueue::pop()
{

    unique_lock<mutex> autoLock(_mutex);

    //bool _flag = true;

    while(empty() && _flag)
    {
        //2.1、如果队列为空，消费者需要睡眠
        _notEmpty.wait(autoLock);
    }
    
    if(_flag){//2.2、如果队列不为空,就可以消费数据
        ElemType tmp = _que.front();
        _que.pop();
    //并且将生产者唤醒
    _notFull.notify_one();
        return tmp;
    }
    else{
        return nullptr;
    }
}

//任务队列是空与满
bool TaskQueue::full() const
{
    return _queSize == _que.size();
}

bool TaskQueue::empty() const
{
    return 0 == _que.size();
}

//唤醒所有线程
void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notify_all();
}