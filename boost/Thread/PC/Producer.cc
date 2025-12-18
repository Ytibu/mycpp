#include "Producer.h"
#include "TaskQueue.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

Producer::Producer(TaskQueue &taskQue)
: _taskQue(taskQue)
{

}

Producer::~Producer()
{

}

void Producer::run()
{
    ::srand(::clock());//种随机种子
    int cnt = 20;
    while(cnt--)
    {
        int number = ::rand() % 100;//产生随机数
        _taskQue.push(number);
        cout << ">>Producer produce number = " << number << endl;
        sleep(1);
    }
}
