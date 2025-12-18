#include <math.h>
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::ostream;

/**
 * 利用类模板和函数模板实现快速排序
 * 类Point 定义点
 * 类模板QuickSort 快速排序
 */

class Point{
public:
    Point(int x = 0, int y = 0): _ix(x), _iy(y){}
    float getDistance() const{
        return hypot(_ix,_iy);
    }

    int getX() const{
        return _ix;
    }
    int getY() const{
        return _iy;
    }

    friend ostream& operator<<( ostream& os, const Point& point) ;

private:
    int _ix;
    int _iy;
};

ostream& operator<<( ostream& os, const Point& point) 
{
    os << "(" << point._ix << "," << point._iy << ")";
    return os;
}


bool operator<(const Point& lhs, const Point& rhs) 
{
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

bool operator>(const Point& lhs, const Point& rhs){
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

struct CompareDistance{
    bool operator()(const Point& lhs, const Point& rhs) const{
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
};


namespace std{  // start of namespace std
    template <>
    struct less<Point>{
        bool operator()(const Point& lhs, const Point& rhs) const{
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
    };

    template<>
    struct greater<Point>{
        bool operator()(const Point& lhs, const Point& rhs){
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
    };
}//end of namespace std


template <typename T>
void swap(T& a, T& b){
    T temp = a;
    a = b;
    b = temp;
};

template<typename T,typename Compare=std::less<T>>
class MyQSort{
public:
    MyQSort(T *arr, size_t size, Compare compare);
    void quickSort(int left, int right, Compare compare);
    int partition(int left, int right,Compare compare);
    void print();
private:
    vector<T> _vec;
};

template<typename T,typename Compare>
MyQSort<T,Compare>::MyQSort(T *arr, size_t size, Compare compare){
    for(size_t i=0;i<size;++i){
        _vec.push_back(arr[i]);
    }
    quickSort(0,_vec.size()-1,compare);
}

template<typename T,typename Compare>
void MyQSort<T,Compare>::quickSort(int left, int right, Compare compare){
    if(left<right){
        int pivot = partition(left,right,compare);
        quickSort(left,pivot-1,compare);
        quickSort(pivot+1,right,compare);
    }
}

template<typename T,typename Compare>
int MyQSort<T,Compare>::partition(int left, int right, Compare compare){ 
    int indexK,indexI;
    for(indexI=left,indexK=left;indexI<right;++indexI){
        if(compare(_vec[indexI],_vec[right])){
            swap(_vec[indexI],_vec[indexK]);
            ++indexK;
        }
    }
    swap(_vec[indexK],_vec[right]);
    return indexK;
}

template<typename T,typename Compare>
void MyQSort<T,Compare>::print(){
    for(auto i:_vec){
        cout<<i<<" ";
    }cout << "\n";
}

int main(){
    int arr[] = {5,4,3,2,1};
    std::less<int> les;
    MyQSort<int> qsort(arr,5,std::less<int>());
    //MyQSort<int, std::greater<int>> qsort2(arr,5,std::greater<int>());

    qsort.print();

    Point par[5] = {Point(1,1),Point(2,2),Point(3,3),Point(4,4),Point(5,5)};
    MyQSort<Point> qsort3(par,5,std::less<Point>());
    qsort3.print();
}