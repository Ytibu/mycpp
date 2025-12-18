#include "EventFd.h"
#include <unistd.h>
#include <iostream>
#include <thread>


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
    EventFd eventFd(std::bind(&MyTask::process, &task));    // 创建一个事件对象

    std::thread th(&EventFd::start, &eventFd);

    // 多次唤醒，确保子线程有任务可以执行
    int cnt = 20;
    while(cnt--){

        cout << "main thread: cnt " << cnt << endl;
        eventFd.wakeup();
        sleep(1);
    }

    eventFd.stop();

    th.join();
}

int main(int argc, char *argv[])
{
    test();
}