#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::shared_ptr;

/**
 * 智能指针shared_ptr的辅助类： enable_shared_from_this
 * 如果一个成员函数返回的是这个类的所有权，就得返回shared_ptr<Point>,
 * 但是返回的shared_ptr<Point>对象是匿名对象，会触发double free
 * 
 * enable_shared_from_this<T>的成员函数shared_from_this()可以返回这个对象的所有权给shared_ptr对象
 * 使用继承或友元成员函数获取shared_ptr对象，以此使用shared_from_this()函数
 */


class Point : public std::enable_shared_from_this<Point> {
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

    Point *addPoint(Point *p) {
        _x += p->_x;
        _y += p->_y;
        return this;
    }

    /*返回的是匿名的shared_ptr，也会出现double free*/
    shared_ptr<Point> addPoint1(Point *p) {
        _x += p->_x;
        _y += p->_y;
        return shared_ptr<Point>(this);
    }

    /*返回的是shared_ptr，它共享 *this 的所有权*/
    shared_ptr<Point> addPoint2(shared_ptr<Point> p) {
        _x += p->_x;
        _y += p->_y;
        return shared_from_this();
    }
private:
    int _x;
    int _y;
};

/*原有的方法：new对象，返回裸指针，裸指针控制对象的生命周期*/
void test(){
    Point *p1 = new Point(1, 2);
    Point *p2 = new Point(3, 4);
    Point *p3 = p1->addPoint(p2);
}

/*新的方法：new对象，返回智能指针，智能指针控制对象生命周期
但是：addPoint1返回的是匿名的shared_ptr，会调用移动构造函数，导致对象被析构
*/
void test1(){
    shared_ptr<Point> p1(new Point(1, 2));
    shared_ptr<Point> p2(new Point(3, 4));
    shared_ptr<Point> p3 = p1->addPoint1(p2.get());
}

/*合理的用法：enable_shared_from_this的成员函数会返回一个共享*this所有权的shared_ptr*/
void test2(){
    shared_ptr<Point> p1(new Point(1, 2));
    shared_ptr<Point> p2(new Point(3, 4));
    shared_ptr<Point> p3 = p1->addPoint2(p2);
    p1.get()->print();
}

int main(){
    //test();   //error
    //test1();  //error
    test2();
}