#include <iostream>

using std::cout;
using std::endl;
/**
 * 资源管理：RAII
 *      构造函数：托管资源
 *      析构函数：释放资源
 *      不允许赋值或复制
 *      提供若干访问资源的方法
 */

class Point
{
public:
    Point(int x = 0, int y = 0) : _x(x), _y(y)
    {
        cout << "Point()" << endl;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }

    void print() const
    {
        cout << "(" << _x << ", " << _y << ")" << endl;
    }

private:
    int _x;
    int _y;
};

template <class T>
class RAII
{
public:
    RAII(T *data) : _data(data)
    {
        cout << "RAII()" << endl;
    }

    ~RAII()
    {
        if (_data)
        {
            delete _data;
            _data = nullptr;
        }
        cout << "~RAII()" << endl;
    }

    RAII(const RAII &) = delete;
    RAII &operator=(const RAII &) = delete;

    T *operator->()
    {
        return _data;
    }
    T &operator*()
    {
        return *_data;
    }
    T *get()
    {
        return _data;
    }
    void set(T *data)
    {
        if (_data)
        {
            delete _data;
        }
        _data = data;
    }

private:
    T *_data;
};

int main()
{

    // RAII<int> raii(new int(10));
    RAII<Point> raii2(new Point(1, 2)); //构造函数(构造函数利用指针开辟堆空间)
    raii2->print(); //raii2实际上是一个指针
    (*raii2).print();
    //析构函数(析构函数会利用指针释放堆空间)

    int *p = new int(20);
    cout << *p << endl;
    delete p;

    Point *p2 = new Point(10, 20);  //堆空间开辟
    p2->print();
    (*p2).print();
    delete p2;  //本身的析构函数不释放资源，因此需要手动delete
}