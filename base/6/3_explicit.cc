#include <iostream>
using std::cout;


/**
 * explicit: 禁止隐式转换
 *      1. 构造函数的参数列表必须包含至少一个非隐式转换的参数
 */


class Point {
public:
    Point(int x = 0, int y = 0)
    : _x(x), _y(y) {
        cout << "Point(" << _x << ", " << _y << ")" << "\n";
    }

    void print() const{
        cout << "Point(" << _x << ", " << _y << ")" << "\n";    
    }
private:
    int _x;
    int _y;
};

int main() {
    Point p(1, 2);
    p.print();
    Point q(3, 4);
    Point r = q;
    Point s = Point(5, 6);
}
