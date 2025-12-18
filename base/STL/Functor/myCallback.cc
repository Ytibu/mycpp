#include <iostream>
#include <functional>
using namespace std::placeholders;
using std::bind;
using std::function;
using std::cout;

struct Functor{
    using disPlayCallback = function<void()>;
    using areaPlayCallback = function<void()>;

    disPlayCallback _disPlayCallback;
    areaPlayCallback _areaPlayCallback;

    void setDisPlayCallback(disPlayCallback&& cb ){
        _disPlayCallback = std::move(cb);
    }

    void setAreaPlayCallback(areaPlayCallback&& cb){
        _areaPlayCallback = std::move(cb);
    }

    void handleDisPlayCallback(){
        if(_disPlayCallback){
            _disPlayCallback();
        }
    }

    void handleAreaPlayCallback(){
        if(_areaPlayCallback){
            _areaPlayCallback();
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

void test(){
    square  sq(10,2);
    sq.display(11.1,12.2);
    sq.areaplay();

    circle ci(3);
    ci.display(9.9);
    ci.areaplay();
}

void test1(){
    Functor F1, F2;
    square  sq(10,2);
    circle ci(3);

    F1.setDisPlayCallback(bind(&square::display, &sq, 10,20));
    F1.setAreaPlayCallback(bind(&square::areaplay, &sq));

    F2.setDisPlayCallback(bind(&circle::display, &ci, 10));
    F2.setAreaPlayCallback(bind(&circle::areaplay, &ci));

    F1.handleAreaPlayCallback();
    F1.handleDisPlayCallback();

    F2.handleDisPlayCallback();
    F2.handleAreaPlayCallback();


}

int main(){

    test();
    test1();
}