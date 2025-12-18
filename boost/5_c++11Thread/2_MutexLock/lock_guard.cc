#include <thread>
#include <mutex>
#include <iostream>

using std::thread;
using std::mutex;
using std::lock_guard;
using std::cout;
using std::endl;


//利用lock_guard实现互斥锁的ARII原则

mutex gMutex;
int gCnt = 0;


void threadFunc(){

    for (size_t i = 0; i < 1000000; i++)
    {
        lock_guard<mutex> lock(gMutex);
        ++gCnt;
    }
    
}



int main(int argc, char *argv[]){

    thread t1(threadFunc);
    thread t2(threadFunc);

    t1.join();
    t2.join();

    cout << "gCnt = " << gCnt << endl;

}