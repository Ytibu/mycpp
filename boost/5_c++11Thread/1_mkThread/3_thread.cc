#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

//线程入口函数传递方式：函数引用的形式

void threadFunc(int x){
    cout << "void threadFunc(int x) "<<endl;
    cout << "x = " << x << endl;
    cout << "child thread id = " << std::this_thread::get_id() << endl; // 获取子线程id
}

int main(int argc, char **argv){

    cout << "main thread id = " << std::this_thread::get_id() << endl;  // 获取主线程id
    typedef void (&pFunc)(int);     //函数引用
    pFunc func = threadFunc;    //引用绑定到变量上
    thread th(func, 33);
    th.join();
}