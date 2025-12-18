#include "Task.h"
#include "ThreadPool.h"
#include <iostream>
#include <time.h>
#include <unistd.h>

using std::cout;
using std::endl;


// 任务类：继承Task，实现process()方法
class MyTask: public Task {
public:
    void process() override {

        ::srand(::clock());//种随机种子
        int number = ::rand() % 100;//产生随机数
        
        cout << "task process: " << number << endl;
    }
};

void test() {

    unique_ptr<Task> ptask(new MyTask());
    ThreadPool pool(4, 10);

    pool.start();

    int cnt = 20;
    while(cnt--) {
        
        pool.addTask(ptask.get());  // 依次添加任务
        cout << "add task: " << cnt << endl;
    }

    pool.stop();
}

int main(int argc, char *argv[]){

    test();

    return 0;
}