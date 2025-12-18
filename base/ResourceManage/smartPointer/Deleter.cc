#include <iostream>
#include <memory>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::shared_ptr;

/**
 * 测试自定义 deleter
 *      1. 创建 unique_ptr 时指定 deleter：unique_ptr<FILE, Deleter>(fp)
 *      2. 创建 shared_ptr 时指定 deleter：Deleter del; shared_ptr<FILE>(fp,del)
 */

struct Deleter {
    void operator()(FILE* p) {
    if(p){
        fclose(p);
        cout << "Deleter::operator()" << endl;
        }
    }
};

void test(){
    string msg = "hello\n";
    unique_ptr<FILE,Deleter> up(fopen("test.txt", "a+"));
    fwrite(msg.c_str(), 1, msg.size(), up.get());
}

void test2(){
    string msg = "hello\n";
    Deleter del;
    shared_ptr<FILE> up(fopen("test.txt", "a+"),del);
    fwrite(msg.c_str(), 1, msg.size(), up.get());
}

int main() {
    
    test2();
}