#include <memory>
#include <iostream>
using std::auto_ptr;
using std::cout;

/**
 * 智能指针：auto_ptr
 * 
 * 特点：
 *      @. auto_ptr对象析构函数会自动释放对象所管理的内存
 * 缺点：
 *      虽然语法层面支持拷贝构造和拷贝复制，但是这样会转移所有权
 *      所有权语义是隐式转换的语义，导致对象无法使用
 */


/*不应执行赋值运算符函数*/
void test(){
    auto_ptr<int> a(new int(10));
    auto_ptr<int> b;
    b = a;
    cout << *a << " " << *b << "\n";
}

/*不应执行拷贝构造函数*/
void test1(){
    auto_ptr<int> a(new int(10));
    auto_ptr<int> b(a);
    cout << *a << " " << *b << "\n";
}

int main(){
    test1();
}