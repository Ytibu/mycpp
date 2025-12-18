#include <iostream>
using std::cout;

/**
 * 函数的重载问题
 *      c语言不支持函数重载，因此必须使用g++编译，gcc无法编译函数重载的代码
 *      核心原因在于：编译器在生成函数符号时，对函数名的处理机制不同
 *      C++ 编译器采用了一种称为 名字修饰 或 名字改编 的技术
 * 函数重载：
 *      函数名相同，返回值相同，参数列表不同
 */

# if 0
int add(int a){
    return a;
}
int add(int a, int b) {
    return a + b;
}
# endif

//如果将函数声明与实现分开编写，默认参数列表必须现在函数声明中定义，不得在实现中定义
int add(int a = 1, int b = 100, int c = 1000) {
    return a + b + c;
}


//在c++的代码中让部分代码按照c的方式编译调用
/* 此方式在{}内会按照c的方式编译代码,即使使用的是c++编译器*/
extern "C" {

#include <stdio.h>
int add(int a, double b){   //此函数按照c的方式编译，因此参数可以类型转换
    return a - b;
}

}//end of extern "C"


int main() {
    cout << "add(): " << add() << "\n";
    cout << "add(a): " << add(1) << "\n";
    cout << "add(a,b): " <<add(1, 2) << "\n";
    cout << "add(a,b,c): " << add(1, 2, 3) << "\n";

    //以下代码按照c的方式编译，因此参数可以类型转换
    cout << "add(a,b): " << add(1.1, 2.2) << "\n";  //此处无法匹配到c++函数，但是可以调用c函数
    cout << "add(a,b): " << add(1, 3.3) << "\n";    //此处虽然无法匹配到c++函数，但是可以调用c函数
}