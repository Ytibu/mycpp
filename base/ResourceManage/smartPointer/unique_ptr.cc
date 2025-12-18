#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::vector;


/**
 * 智能指针:
 * 
 * 特点：
 *      1. 具有对象语义：语法不支持拷贝构造和拷贝复制，但是支持移动
 *      2. 独享所有权的智能指针
 *      3. 可以作为容器的元素：只有右值的unique_ptr可以作为容器的元素
 * 构建右值的unique_ptr：
 *       1. std::move
 *       2.直接使用unique_ptr的构造函数，创建匿名对象
 */

class Point{
public:
    Point(int x=0, int y=0):_x(x), _y(y){
        cout << "Point()" << endl;
    }

    ~Point(){
        cout << "~Point()" << endl;
    }

    void print() const {
        cout << "(" << _x << ", " << _y << ")" << endl;
    }
private:
    int _x;
    int _y;
};

void test(){
    unique_ptr<int> p(new int(10));
    cout << *p << endl; //获取指针解引用内容
    cout << p.get() << endl;    //获取指针
}


void test0()
{
    unique_ptr<int> p1(new int(10));
    // unique_ptr<int> p2(p1);  // error,unique_ptr独享资源控制权,无法进行拷贝
    cout << *p1 << endl;
    unique_ptr<int> p2(move(p1));   // move
    cout << *p2 << endl;

    // cout << "**p1 = " << *p1 << endl;
    //cout << "p1.get() = " << p1.get() << endl;

    unique_ptr<int> p3(new int(10));    //两个new int(10)是不同的内存区域

}

void test1()
{
    unique_ptr<Point> p1(new Point(4,9));
    vector<unique_ptr<Point>> vec;  //可以作为容器的元素
    vec.push_back(std::move(p1));    // 显示转移所有权：std::move，将左值转换为右值
    vec.push_back(unique_ptr<Point>(new Point(5,6)));   //unique_ptr作为元素
    for(auto &p : vec){
        p->print();
    }
    auto i = *p1;
    //cout << "**p1 = " << *p1 << endl;

}

int main()
{
    test();
    test0();
    test1(); 
}