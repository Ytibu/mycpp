#include <math.h>

#include <iostream>
#include <vector>

using std::vector;
using std::cout;


class Point{
public:
    Point(int x, int y):_x(x), _y(y){}
    float getDistance()const{
        return hypot(_x, _y);
    }
    int getX()const{
        return _x;
    }
    int getY()const{
        return _y;
    }
    friend bool operator<(const Point &lhs, const Point &rhs);
    friend bool operator>(const Point &lhs, const Point &rhs);
    friend std::ostream &operator<<(std::ostream os, const Point &point);
private:
    int _x;
    int _y;
};

bool operator<(const Point &lhs, const Point &rhs){
    if(lhs.getDistance() < rhs.getDistance()){
        return true;
    }else if(lhs.getDistance() == rhs.getDistance()){
        if(lhs.getX() < rhs.getX()){
            return true;
        }else if(lhs.getX() == rhs.getX()){
            if(lhs.getY() < rhs.getY()){}
        }
    }
}

bool operator>(const Point &lhs, const Point &rhs){
    if(lhs.getDistance() > rhs.getDistance()){
        return true;
    }else if(lhs.getDistance() == rhs.getDistance()){
        if(lhs.getX() > rhs.getX()){
            return true;
        }else if(lhs.getX() == rhs.getX()){
            if(lhs.getY() > rhs.getY()){}
        }
    }
}

std::ostream &operator<<(std::ostream os, const Point &point){
    os << "(" << point.getX() << ", " << point.getY() << ")";
    return os;
}



namespace std{
    template<>
    class less<Point>{
    public:
        bool operator()(const Point &lhs, const Point &rhs){
            if(lhs.getDistance() < rhs.getDistance()){
                return true;
            }else if(lhs.getDistance() == rhs.getDistance()){
                if(lhs.getX() < rhs.getX()){
                    return true;
                }else if(lhs.getX() == rhs.getX()){
                    if(lhs.getY() < rhs.getY()){
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
    };//class less<Point>

    template<>
    class greater<Point>{
    public:
        bool operator()(const Point &lhs, const Point &rhs){
            if(lhs.getDistance() > rhs.getDistance()){
                return true;
            }else if(lhs.getDistance() == rhs.getDistance()){
                if(lhs.getX() > rhs.getX()){
                    return true;
                }else if(lhs.getX() == rhs.getX()){
                    if(lhs.getY() > rhs.getY()){
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
    };//class greater<Point>
}

struct PointCompareGreater{
    bool operator()(const Point &lhs, const Point &rhs){
        if(lhs.getDistance() > rhs.getDistance()){
            return true;
        }else if(lhs.getDistance() == rhs.getDistance()){
            if(lhs.getX() > rhs.getX()){
                return true;
            }else if(lhs.getX() == rhs.getX()){
                if(lhs.getY() > rhs.getY()){
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
};//struct PointCompareGreater

struct PointCompareLess{
    bool operator()(const Point &lhs, const Point &rhs){
        if(lhs.getDistance() < rhs.getDistance()){
            return true;
        }else if(lhs.getDistance() == rhs.getDistance()){
            if(lhs.getX() < rhs.getX()){
                return true;
            }else if(lhs.getX() == rhs.getX()){
                if(lhs.getY() < rhs.getY()){
                    return true;
                }else{
                    return false;
                }
            }
        }
    }
};//struct PointCompareLess

template<typename T,  typename Compare = std::less<T>>
class headSort{
public:
    headSort(T *arr, size_t size, Compare &compare);
    void headAdjust(size_t sizeI, size_t sizeK, Compare &compare);
    void sort(Compare &compare);
    void print();
private:
    vector<T> _vec;
};

template<typename T, typename Compare>
headSort<T, Compare>::headSort(T *arr, size_t size, Compare &compare){
    for(size_t i = 0; i < size; ++i){
        _vec.push_back(arr[i]);
    }
    sort(compare);
}

template<typename T, typename Compare>
void headSort<T,Compare>::sort(Compare &compare){
    for(size_t i = _vec.size() / 2; i > 0; --i){
        headAdjust(_vec.size(), i, compare);
    }
}

template<typename T, typename Compare>
void headSort<T,Compare>::headAdjust(size_t sizeI, size_t sizeK, Compare &compare){
}