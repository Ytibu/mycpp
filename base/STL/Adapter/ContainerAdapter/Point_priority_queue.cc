#include <math.h>

#include <vector>
#include <queue>
#include <iostream>
#include <utility>

using std::cout;
using std::vector;
using std::priority_queue;
using std::ostream;

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
    struct less<Point>{
        bool operator()(const Point &lhs, const Point &rhs) const{
            if(lhs.getdisance()<rhs.getdisance()){
                return true;
            }
        }
    };
}//namespace std


struct ComparePoint{
    bool operator()(const Point &p1, const Point &p2) const{
        return p1.getX() < p2.getX() || (p1.getX() == p2.getX() && p1.getY() < p2.getY());
    }
};//struct ComparePoint

int main(){

    vector<Point> points{
        Point(1,2),
        Point(2,3),
        Point(3,4),
        Point(4,5),
        Point(5,6),
        Point(6,7),
        Point(7,8),
        Point(8,9),
        Point(9,10)
    };
    priority_queue<Point, vector<Point>, ComparePoint> pq(points.begin(), points.end());

    while (!pq.empty())
    {
        cout << pq.top() << "\n";
        pq.pop();
    }cout << "\n";
    
}