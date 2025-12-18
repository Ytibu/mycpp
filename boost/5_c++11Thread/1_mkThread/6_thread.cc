#include <iostream>
#include <thread>
#include <functional>

using std::cout;
using std::endl;
using std::thread;
using std::bind;
using std::function;


// 线程入口函数传递方式：绑定函数


void threadFunc(int x){
    cout << "void threadFunc(int x) "<<endl;
    cout << "x = " << x << endl;
    cout << "child thread id = " << std::this_thread::get_id() << endl; // 获取子线程id
}

int main(int argc, char *argv[]){

    // 获取主线程id
    cout << "main thread id = " << std::this_thread::get_id() << endl;  //获取本线程的id函数
    
    using namespace std::placeholders;
    function<void(int)> f = bind(threadFunc, _1);   // 绑定函数threadFunc
    thread th(f, 66);

    th.join();
}
