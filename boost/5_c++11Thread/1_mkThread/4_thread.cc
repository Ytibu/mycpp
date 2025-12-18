#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

// 线程入口函数传递方式：函数对象的形式

class Example{
public:
    void operator()(int x){
        cout << "void operator()(int x) "<<endl;
        cout << "x = " << x << endl;
        cout << "child thread id = " << std::this_thread::get_id() << endl; // 获取子线程id
    }
};


int main(int argc, char *argv[]){

    cout << "main thread id = " << std::this_thread::get_id() << endl;

    Example example;    // 创建函数对象

    thread t(example, 44);   //使用函数对象作为线程入口函数
    t.join();

}