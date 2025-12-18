#include <iostream>
using std::cout;


//#include "Point.h"
#ifndef __POINT_H__
#define __POINT_H__ 
#include <iostream>
using std::cout;
class Point{
public:
    Point(int x, int y);
    ~Point();
    void print();

private:
    int _x = 0; //c++11之后
    int _y = 0;
};
#endif  //__POINT_H__


Point::Point(int x, int y)
: _x(x), _y(y)  //参数列表初始化为最早的初始化方式 
{

}
Point::~Point(){

}
void Point::print()
{
    cout << "(" << _x << ", " << _y << ")" << "\n";
}

int main()
{
    Point p(1, 2);
    p.print();
}