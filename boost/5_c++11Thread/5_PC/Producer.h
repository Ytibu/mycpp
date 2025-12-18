#ifndef __PRODUCER_H__
#define __PRODUCER_H__


class TaskQueue;

class Producer
{
public:
    Producer();
    ~Producer();

    void run(TaskQueue &taskQue);

};

#endif
