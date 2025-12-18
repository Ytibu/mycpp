#include <iostream>
using std::cout;

/**
 * TypeCast，c++的强制转换
 *      static_cast<T>(expression) :最常用，用于指针之间的转换
 *      const_cast<T>(expression) :用于去除const和volatile,即去除常量属性
 *      dynamic_cast<T>(expression) :用于多态类之间的转换,基类与派生类之间
 *      reinterpret_cast<T>(expression) :任意类型间的转换，如指针与整数之间
 */


/* static_cast */
void test0(){
    int *pint = (int *)malloc(sizeof(int));
    *pint = 10;

    int *pint2 = static_cast<int *>(malloc(sizeof(int)));
    *pint2 = 100;
}

/* 修改p指针的指向对象的值 */
void func(int * p){
    *p = 100;
    cout << "*p: " << *p << "\n";
}/*const_cast*/
void test1(){
    const int number = 1;
    //func(&number);    
    // error: func()期望收到一个int*参数，但是实际收到一个const int*参数
    cout << "number: " << number << "\n";
    func(const_cast<int *>(&number));   //函数内部可以修改，但是全局不变
    cout << "number: " << number << "\n";
    //可以理解为：只在寄存器上进行修改使用，但是没有写会到内存
}

int main(){
    test0();
    test1();
}