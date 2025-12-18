#include "Consumer.h"
#include "Producer.h"
#include "TaskQueue.h"
#include <iostream>
#include <thread>


using std::cout;
using std::endl;
using std::thread;


//利用c++11的thread库，实现生产者消费者模型，同时利用"锁和条件变量(mutex,condition_variable)"实现线程安全

void test(){

    TaskQueue taskQue(10);  //创建taskQueue对象的时候，将创建全局唯一的锁，同时创建两个条件变量
    
    Producer producer;
    Consumer consumer;

    thread pro(&Producer::run, &producer, std::ref(taskQue));
    thread con(&Consumer::run, &consumer, std::ref(taskQue));

    pro.join();
    con.join();

}

int main(int argc, char **argv){
    test();
    return 0;
}