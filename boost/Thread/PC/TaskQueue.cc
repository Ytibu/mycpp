#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
{

}

TaskQueue::~TaskQueue()
{

}

//添加任务
void TaskQueue::push(const int &value)
{
    //使用C++之父提出的RAII的思想
    //核心：利用栈对象的生命周期管理资源
    //1、上锁
    /* _mutex.lock(); */
    MutexLockGuard autoLock(_mutex);

    //2、是不是满
    /* if(full()) */
    while(full())
    {
        //2.1、如果队列是满的，生产者需要睡眠
        _notFull.wait();
    }
    //2.2、如果队列不为满才能进行push操作
    _que.push(value);
    //并且将消费者唤醒
    _notEmpty.notify();

    //3、解锁
    /* _mutex.unlock(); */
}

//获取任务
int TaskQueue::pop()
{
    /* int tmp = 0; */
    /* { */
    //1、上锁
    /* _mutex.lock(); */
    MutexLockGuard autoLock(_mutex);

    //2、是不是空
    /* if(empty()) */
    while(empty())
    {
        //2.1、如果队列为空，消费者需要睡眠
        _notEmpty.wait();
    }
    //2.2、如果队列不为空,就可以消费数据
    int tmp = _que.front();
    _que.pop();
    //并且将生产者唤醒
    _notFull.notify();
    //3、解锁
    /* _mutex.unlock(); */
    /* } */

    return tmp;
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
