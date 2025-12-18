#include <thread>
#include <mutex>
#include <iostream>

using std::thread;
using std::mutex;
using std::unique_lock;
using std::cout;
using std::endl;


//利用unique_lock可以实现提前释放锁，支持手动控制锁的获取和释放时机，精细化控制锁

mutex gMutex;
int gCnt = 0;


void threadFunc(){

    for (size_t i = 0; i < 1000000; i++)
    {
        unique_lock<mutex> ulock(gMutex);
        ++gCnt; //互斥资源
        // xxxx
        ulock.unlock();

        // yyyy

        ulock.lock();
        // zzzz
        ulock.unlock();
    }
    
}



int main(int argc, char *argv[]){

    thread t1(threadFunc);
    thread t2(threadFunc);

    t1.join();
    t2.join();

    cout << "gCnt = " << gCnt << endl;

}