#include <iostream>
using namespace std;

class Point{
public:
    /*如果静态成员变量没有初始化，则对其进行初始化*/
    static Point *getInstance(int x,int y){
        if(_instance == nullptr){
            _instance = new Point(x,y);
        }
        return _instance;
    }

    /*如果静态成员变量有初始化，则销毁*/
    static void destroy(){
        if(_instance != nullptr){
            delete _instance;
            _instance = nullptr;
        }
    }

    void print(){
        cout << "x:" << _x << " y:" << _y << endl;
    }

private:
    int _x,_y;

    Point() = default;
    /*类的初始化交给getInstance()函数,getInstance()函数会确保静态成员变量只被初始化一次*/
    Point(int x,int y):_x(x),_y(y){}
    ~Point(){}
    Point(const Point &) = delete;  //禁止拷贝构造
    Point &operator=(const Point &) = delete;   //禁止赋值拷贝

    static Point *_instance;    // 静态成员变量
};
Point *Point::_instance = nullptr;  // 先将静态成员设置为空，未初始化

void test(){ 
    /*创建对象：此共有对象调用私有的构造函数初始化对象*/
    Point *p = Point::getInstance(1,2);
    /*创建对象，但是此前已经在静态区创建了一个对象，因此不会创建对象只会返回引用*/
    Point *p1 = Point::getInstance(1,2);
    cout  << p << " " << p1 << endl;
    p->destroy();
    p1->print();
}

void test1(){
    
    Point::getInstance(1,2)->print();   //设计的不完美的此单例模式对象应该也必须使用这种调用方法
    Point::destroy();
}

int main(){
    test1();
    return 0;
}