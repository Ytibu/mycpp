#include <iostream>
#include <thread>
#include <mutex>


using std::thread;
using std::mutex;
using std::cout;
using std::endl;

//使用互斥锁确保线程安全

mutex gMutex;
int gCnt = 0;


void threadFunc(){

    for (size_t i = 0; i < 1000000; i++)
    {
        gMutex.lock();
        ++gCnt;
        gMutex.unlock();
    }
    
}

int main(int argc, char *argv[]){

    thread t1(threadFunc);
    thread t2(threadFunc);

    t1.join();
    t2.join();

    cout << "gCnt = " << gCnt << endl;


}