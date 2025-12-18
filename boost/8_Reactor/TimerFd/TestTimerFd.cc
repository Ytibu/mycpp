#include "TimerFd.h"
#include <unistd.h>
#include <iostream>
#include <thread>
#include <functional>


using std::cout;
using std::endl;

// 任务类
class MyTask{
public:
    void process()
    {
        cout << "MyTask::process()" << endl;
    }
};

void test(){

    MyTask task;    // 任务对象
    TimerFd timerFd(std::bind(&MyTask::process, &task), 1, 5);    // 创建一个事件对象
    std::thread th(&TimerFd::start, &timerFd);

    sleep(30);

    timerFd.stop();

    th.join();
}

int main(int argc, char *argv[])
{
    test();
}