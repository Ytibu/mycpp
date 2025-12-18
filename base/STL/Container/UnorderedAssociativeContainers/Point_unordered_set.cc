#include <math.h>

#include <iostream>
#include <unordered_set>

using std::cout;
using std::unordered_set;


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
private:
    int _ix;
    int _iy;
};


std::ostream &operator<<( std::ostream &os, const Point &p){
    os << "(" << p._ix << "," << p._iy << ")";
    return os;
}


namespace std{
    template<>
    struct hash<Point>{
        size_t operator()(const Point& point) const{
            return ((point.getX() << 1) ^ (point.getY() << 2));
        }
    };// struct hash
}// namespace std

struct hashPoint{
    size_t operator()(const Point& point) const{
        return ((point.getX() << 1) ^ (point.getY() << 2));
    }
};// struct hashPoint

bool operator==(const Point &p1, const Point &p2){
    return (p1.getX() == p2.getX()) && (p1.getY() == p2.getY());
}

namespace std{
    template<>
    struct equal_to<Point>{
        bool operator()(const Point &lhs, const Point &rhs) const{
            return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
        }
    };// struct equal_to
}// namespace std

struct EqualToPoint{
    bool operator()(const Point &lhs, const Point &rhs) const{
        return (lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY());
    }
};// struct EqualToPoint

template<typename Container>
void display(Container const &c) {
    for (auto const &elem : c) {
        cout << elem << " ";
    }cout << "\n";
}


/*使用自定义对象时：可以通过模板特化std::hash<Point>和std::equal_to<Point>
可以通过类对象创建哈希表和关联容器
equal_to<Point>可以手动实现bool operator()(const Point &lhs, const Point &rhs) const{}
*/
void test(){

    unordered_set<Point> points {
        Point(1,2),
        Point(2,3),
    };

    unordered_set<Point, hashPoint> points1 {
        Point(1,2),
        Point(2,3),
    };

    unordered_set<Point, hashPoint, std::equal_to<Point>> points2 {
        Point(1,2),
        Point(2,3),
    };

    unordered_set<Point, hashPoint, EqualToPoint> points3 {
        Point(1,2),
        Point(2,3),

    };

    display(points);
    display(points1);
    display(points2);
    display(points3);

}
int main(){
    test();
}