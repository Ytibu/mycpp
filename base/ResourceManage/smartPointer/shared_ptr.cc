#include <memory>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::move;
using std::shared_ptr;
using std::vector;

/**
 * shared_ptr:
 *      1. 共享所有权的智能指针：多个指针可以控制同一个内存，可以使用引用计数来巨鹿对象的个数
 *      2. 具有拷贝复制和拷贝赋值：具有值语义
 *      4. 具有移动构造和移动复制：具有移动语义
 *      4. 可以作为容器的元素：可以传递左值，也可以传递右值
 */

/*共享所有权，可以通过use_count()查看引用计数*/
void test1()
{
    shared_ptr<int> p1(new int(10));
    cout << "*p1: " << *p1 << endl;
    cout << "p1.get(): " << p1.get() << endl;

    shared_ptr<int> p2(p1);
    cout << "*p2: " << *p2 << endl;
    cout << "p2.get(): " << p2.get() << endl;

    cout << "p1.use_count(): " << p1.use_count() << endl;
    cout << "p2.use_count(): " << p2.use_count() << endl;
}

/*值语义：支持拷贝构造和拷贝赋值，并且共享所有权*/
void test2()
{

    shared_ptr<int> p1(new int(10));
    shared_ptr<int> p2 = p1; // 拷贝构造
    cout << "*p1: " << *p1 << endl;
    cout << "*p2: " << *p2 << endl;
    cout << "p1.use_count(): " << p1.use_count() << endl;

    shared_ptr<int> p3(new int(20));
    shared_ptr<int> p4;
    p4 = p3; // 拷贝赋值
    cout << "*p3: " << *p3 << endl;
    cout << "*p4: " << *p4 << endl;
    cout << "p3.use_count(): " << p3.use_count() << endl;
}

void test3()
{

    // 可以直接作为容器的元素，不考虑是否为右值
    shared_ptr<int> p1(new int(10));
    shared_ptr<int> p2(new int(20));
    vector<shared_ptr<int>> vec;

    vec.push_back(p1);
    vec.push_back(move(p2));
    vec.push_back(shared_ptr<int>(new int(30)));
    for (size_t i = 0; i < 3; i++)
    {
        cout << "*vec[" << i << "]: " << *vec[i] << endl;
    }
}

/*值语义：支持移动构造和移动赋值，但是会转移所有权，
旧对象的引用计数为0，新对象的引用计数为1*/
void test4()
{

    shared_ptr<int> p1(new int(10));
    shared_ptr<int> p2;
    p2 = std::move(p1); // 移动赋值

    // cout << "*p1: " << *p1 << endl;
    cout << "*p2: " << *p2 << endl;
    cout << "p1.use_count(): " << p1.use_count() << endl;
    cout << "p2.use_count(): " << p2.use_count() << "\n";

    shared_ptr<int> p3(new int(10));
    shared_ptr<int> p4 = std::move(p3); // 移动构造

    // cout << "*p3: " << *p3 << endl;
    cout << "*p4: " << *p4 << endl;
    cout << "p3.use_count(): " << p3.use_count() << endl;
    cout << "p4.use_count(): " << p4.use_count() << "\n";
}
int main()
{
    test1();
    test2();
    test3();
    test4();
}