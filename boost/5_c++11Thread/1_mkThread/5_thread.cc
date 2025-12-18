#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

// 线程入口函数传递方式：lambda表达式


int main(int argc, char *argv[]){

    cout << "main thread id = " << std::this_thread::get_id() << endl;

    //lambda表达式
    thread th([](int x){

        cout << "x = " << x << endl;
        cout << "child thread id = " << std::this_thread::get_id() << endl; // 获取子线程id
    }, 55);

    th.join();

}