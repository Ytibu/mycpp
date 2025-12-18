#include "Thread.h"
#include "Consumer.h"
#include "Producer.h"
#include "TaskQueue.h"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

void test(){

    TaskQueue taskQue(10);  //创建taskQueue对象的时候，将创建全局唯一的锁，同时创建两个条件变量
    
    unique_ptr<Thread> pro(new Producer(taskQue));
    unique_ptr<Thread> con(new Consumer(taskQue));

    pro->start();
    con->start();

    pro->stop();
    con->stop();
    
}

int main(int argc, char **argv){
    test();
    return 0;
}