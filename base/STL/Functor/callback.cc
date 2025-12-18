#include <iostream>
#include <functional>
#include <math.h>
using std::cout;
using std::function;
using std::move;
using namespace std::placeholders;

/**
 * 函数对象的回调函数使用: 声明，设置回调函数，设置回调函数的回调执行函数。
 */

class Functor {
public:
    using DisPlayCallback = function<void()>;
    using AreaPlayCallback = function<double()>;
    //定义两个函数对象

    DisPlayCallback _displayCallback;
    AreaPlayCallback _areaCallback;
    //设置函数对象，存储回调函数对象

    //设置回调函数的回调方式
    void setDisPlayCallback(DisPlayCallback &&callback) {
        _displayCallback = std::move(callback);
    }
    void setAreaPlayCallback(AreaPlayCallback &&callback) {
        _areaCallback = std::move(callback);
    }

    //回调函数的回调--回调执行方式
    void handleDisPlayCallback() {
        if (_displayCallback) {
            _displayCallback();
        }
    }
    void handleAreaPlayCallback() {
        if (_areaCallback) {
            _areaCallback();
        }
    }
};

class circle{
public:
    circle(double r):radius(r){}
    double getArea() {
        return 3.14 * radius * radius;
    }
    void display(double r){
        cout << "circle::display radius: " << r << "\n";
    }
    double areaplay(){
        cout << "circle::areaplay area: " << 2*radius*radius*3.14 << "\n";
        return 2*radius*radius*3.14;
    }
private:
    double radius;
};

class square{
public:
    square(double w,double h):width(w),height(h){}
    double getArea(){
        return width * height;
    }

    void display(double w, double h){
        cout << "square::display width:" << w << " height:" << h << "\n";
    }

    double areaplay(){
        cout << "square::areaplay area:" << width * height << "\n";
        return width * height;
    }
private:
    double width;
    double height;
};

void func(Functor& f){
    f.handleDisPlayCallback();
    f.handleAreaPlayCallback();
}

int main(){ 

    Functor f1,f2;
    
    //调用Functor类的setCallback()来存储函数对象：circle的成员函数绑定成函数对象
    circle c(5);
    f1.setDisPlayCallback(std::bind(&circle::display,&c,7)); //存储函数对象时：将需要的参数绑定给函数对象
    f1.setAreaPlayCallback(std::bind(&circle::areaplay,&c));

    //调用Fucntor类的handleCallback()来调用函数对象执行函数：将存储的circle的成员函数调用
    func(f1);

    square r(5,10);
    f2.setDisPlayCallback(std::bind(&square::display,&r,8,9));
    f2.setAreaPlayCallback(std::bind(&square::areaplay,&r));
    func(f2);

}