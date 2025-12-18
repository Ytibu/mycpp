#include <memory>
#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;

/**
 * shared_ptr的循环引用问题：
 *      类互相持有对方的shared_ptr
 *      shared_ptr的引用计数会无限增加
 *  问题：程序结束后无法自动调用析构函数，无法释放资源
*/ 

class Child;

class Parent
{
public:
    Parent() { cout << "Parent()" << endl; }
    ~Parent() { cout << "~Parent()" << endl; }
    shared_ptr<Child> spChild;
};

class Child
{
public:
    Child() { cout << "Child()" << endl; }
    ~Child() { cout << "~Child()" << endl; }
    shared_ptr<Parent> spParent;
};

void test()
{

    shared_ptr<Parent> parentPtr(new Parent());
    shared_ptr<Child> childPtr(new Child());
    cout << "parentPtr.use_count() = " << parentPtr.use_count() << endl;
    cout << "childPtr .use_count() = " << childPtr.use_count() << endl;

    parentPtr->spChild = childPtr;
    childPtr->spParent = parentPtr;
    // 获取到的引用计数都是2
    cout << "parentPtr.use_count() = " << parentPtr.use_count() << endl;
    cout << "childPtr.use_count()  = " << childPtr.use_count() << endl;
}

int main()
{
    test();
}