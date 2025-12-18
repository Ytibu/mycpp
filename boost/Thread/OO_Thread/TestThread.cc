#include <iostream>
#include "Thread.h"
#include <unistd.h>
#include <memory>

using namespace std;

//通过继承封装过的线程类，来实现线程的创建与使用

class MyThread: public Thread
{
public:
    void run() override{
        int i = 0;
        while(i < 5){
            cout << "MyThread run" << endl;
            sleep(1);
            ++i;
        }

    }

};

void test()
{
    MyThread t;
    t.start();
    sleep(5);
    t.stop();
}

void test1()
{
    unique_ptr<Thread> up(new MyThread());
    up->start();
    sleep(5);
    up->stop();
}

int main(int argc, char **argv){
    test();
    //test1();
}