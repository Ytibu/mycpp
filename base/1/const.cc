#include <iostream>
using std::cout;
#define MAX 100
#define MIN HELLO

/**
 * const 常量的使用
 */


/*宏定义的使用*/
void test(){
    cout << MAX << "\n";    //宏定义也是常量
    //cout << 100 - MIN << "\n";  //宏定义不会做类型检查

    const int min = 10;

    //const int max;  //const必须初始化且只能赋值一次
    const int max = 20;
    //max = 30;   //const常量只能赋值一次

}

/*常量指针*/
void test1(){
    int num = 100;
    int num2 = 200;
    const int * p = &num;
    cout << *p << "\n";

    //*p = 200; 错误:const修饰指针，不能修改指针指向的内容的值，即不得采用解引用修改指针指向的内容的值
    p = &num2;  //正确:const修饰指针，可以修改指针指向的内容的指针本身
    cout << *p << "\n";

}

/*常量指针*/
void test2(){
    int num = 100;
    int num2 = 200;
    int const * p = &num;
    cout << *p << "\n";

    //*p = 200;   //错误:const修饰指针，不能修改指针指向的内容的值，即不得采用解引用修改指针指向的内容的值
    p = &num2;  //正确:const修饰指针，可以修改指针指向的内容的指针本身
    cout << *p << "\n";
}

/*指针常量*/
void test3(){
    int num = 100;
    int num2 = 200;
    int * const p = &num;
    cout << *p << "\n";

    *p = 300;   //正确:指针修饰const，可以修改指针指向的内容的值，即可以采用解引用修改指针指向的内容的值
    //p = &num2;  //错误:指针修饰const，不能修改指针指向的内容的指针本身
    cout << *p << "\n";
}
int main(){
    test();
    test1();
    test2();
    test3();
}