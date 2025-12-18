#include <iostream>
#include <map>
using std::cout;
using std::multimap;

/**关联式容器：multimap
 * 描述：multimap 是关联式容器，有序容器，键值对允许重复
 *      key值为排序的关键，
 * 使用的迭代器：前序迭代器
 */

 class Point{
public:
    Point(int x = 0, int y = 0)
    :_ix(x), _iy(y)
    {}

    ~Point(){}

    float getdisance() const{
        return hypot(_ix,_iy);
    }
    int getX() const{
        return _ix;
    }
    int getY() const{
        return _iy;
    }

    friend std::ostream& operator<<( std::ostream& os, const Point& p); //重载输出流
    friend bool operator<(const Point& p1, const Point& p2);    //重载小于运算符
    friend struct ComparePoint; //定义比较结构体(函数对象)

private:
    int _ix;
    int _iy;
};

std::ostream &operator<<( std::ostream &os, const Point &p){
    os << "(" << p._ix << "," << p._iy << ")";
    return os;
}


void test(){

}

/*容量*/
void test1(){


}

/*修改器*/
void test2(){

}

/*查找*/
void test3(){

}
int main(){
    test();
    test1();
    test2();
    test3();
}