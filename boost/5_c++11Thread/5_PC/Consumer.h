#ifndef __CONSUMER_H__
#define __CONSUMER_H__


class TaskQueue;

class Consumer
{
public:
    Consumer();
    ~Consumer();

    void run(TaskQueue &taskQue);


};

#endif
