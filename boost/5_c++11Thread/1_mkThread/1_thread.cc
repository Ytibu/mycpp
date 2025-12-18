#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

//线程入口函数传递方式：普通函数的形式

void threadFunc(int x){
    cout << "void threadFunc(int x) "<<endl;
    cout << "x = " << x << endl;
    cout << "child thread id = " << std::this_thread::get_id() << endl; // 获取子线程id
}

int main(int argc, char **argv){

    cout << "main thread id = " << std::this_thread::get_id() << endl;  // 获取主线程id

    // 创建子线程
    thread th(threadFunc, 11);  //传入函数，及其函数参数

    // 阻塞主线程，等待子线程结束
    th.join();  
}