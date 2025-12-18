#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::unique_ptr;


/**
 * 裸指针常见的滥用问题
 */

class Point
{
public:
    Point(int ix = 0, int iy = 0)
        : _ix(ix), _iy(iy)
    {
        cout << "Point(int=0,int=0)" << endl;
    }

    void print() const
    {
        cout << "(" << _ix
             << "," << _iy
             << ")" << endl;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }

private:
    int _ix;
    int _iy;
};

/*禁止向智能指针传入裸指针*/
void test()
{

    // 需要人为注意避免
    Point *pt = new Point(1, 2);
    unique_ptr<Point> up(pt);  // 禁止传入裸指针
    unique_ptr<Point> up2(pt); // 禁止传入裸指针

    // 禁止传入指针
    Point *p = new Point(1, 2);
    shared_ptr<Point> sp(p);
    shared_ptr<Point> sp2(p);
}

/*智能指针的get()会获取裸指针，使用时要注意*/
void test1()
{
    unique_ptr<Point> up(new Point(1, 2));
    unique_ptr<Point> up2(new Point(1, 2));
    up.reset(new Point(8, 9)); // 回收上一个对象，并重新分配内存，指向新空间
    up.reset(up2.get());       // up2.get()返回裸指针，up接收裸指针会引起double free

    shared_ptr<Point> sp(new Point(1, 2));
    shared_ptr<Point> sp2(new Point(1, 2));
    sp.reset(new Point(8, 9)); // 回收上一个对象，并重新分配内存，指向新空间
    sp.reset(sp2.get());       // 返回裸指针，up接收裸指针会引起double free
}

int main(void)
{
    test();
    test1();
    return 0;
}
