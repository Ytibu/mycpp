#include <iostream>
#include <set>
#include <math.h>
using std::set;

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

/*运算符重载*/
bool operator<(const Point& p1, const Point& p2){
    if(p1.getdisance() < p2.getdisance()){
        return true;
    }else if(p1.getdisance() == p2.getdisance()){
        if(p1.getX() < p2.getX()){
            return true;
        }else if(p1.getX() == p2.getX()){
            if(p1.getY() < p2.getY()){
                return true;
            }else{
                return false;
            }
        }else{  
            return false;
        }
    }else{
        return false;
    }
}

/*函数对象*/
struct ComparePoint{
    bool operator()(const Point& p1, const Point& p2) const{
        if(p1.getdisance() < p2.getdisance()){
            return true;
        }else if(p1.getdisance() == p2.getdisance()){
            if(p1.getX() < p2.getX()){
                return true;
            }else if(p1.getX() == p2.getX()){
                if(p1.getY() < p2.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{  
                return false;
            }
        }else{
            return false;
        }
    }
};


/*模板特化*/
namespace std{
    template<>
    struct less<Point>{
        bool operator()(const Point& p1, const Point& p2) const{
            if(p1.getdisance() < p2.getdisance()){
                return true;
            }else if(p1.getdisance() == p2.getdisance()){
                if(p1.getX() < p2.getX()){
                    return true;
                }else if(p1.getX() == p2.getX()){
                    if(p1.getY() < p2.getY()){
                        return true;
                    }else{
                        return false;
                    }
                }else{  
                    return false;
                }
            }else{
                return false;
            }
        }
    };
}


int main(){ 

    set<Point> points{
        Point(1,1),
        Point(1,2),
        Point(2,1),
        Point(2,2)
    };
}