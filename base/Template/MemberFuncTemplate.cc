#include <iostream>
using std::cout;

/**成员函数模板 */

class Point
{
public:
    Point(double ix = 0, double iy = 0)
        : _ix(ix), _iy(iy)
    {
    }

    template <typename T = int>
    T convert()
    {
        return (T)_ix;
    }

    template <typename T>
    T add(T t);

private:
    double _ix;
    double _iy;
};

template <typename T>
T Point::add(T t)
{
    return _ix + _iy + t;
}

int main(void)
{
    Point pt(10.11, 20.22);
    cout << pt.convert() << "\n";      // 使用模板参数类型的默认值
    cout << pt.convert<int>() << "\n"; // 使用模板参数类型的指定值
}