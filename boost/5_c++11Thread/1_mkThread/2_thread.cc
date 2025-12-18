#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

//线程入口函数传递方式：函数指针的形式

void threadFunc(int x){
    cout << "void threadFunc(int x) "<<endl;
    cout << "x = " << x << endl;
    cout << "child thread id = " << std::this_thread::get_id() << endl; // 获取子线程id
}

int main(int argc, char **argv){

    cout << "main thread id = " << std::this_thread::get_id() << endl;  // 获取主线程id
    typedef void (*pFunc)(int);  // 定义函数指针
    pFunc func = &threadFunc;   // 函数指针赋值
    thread th(func, 22);      // 创建子线程
    th.join();  // 阻塞主线程，等待子线程结束
}
