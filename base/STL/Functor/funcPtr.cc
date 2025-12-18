#include <iostream>
using std::cout;

/**
 * 函数指针
 * 函数指针的声明方式：
 *    1.传统C：typedef return_type (*pFunc)(arg_type1, arg_type2, ...);
 *    2.C++别名：using pFunc = return_type (*)(arg_type1, arg_type2, ...);
 *    3.函数类型别名+指针使用：using pFunc = return_type (arg_type1, arg_type2, ...);
 *                              pFunc* p = &func_name;
 *    4.直接声明函数指针变量：return_type (*p)(arg_type1, arg_type2, ...) = &func_name;
 * 
 * 回调函数：允许将函数作为参数传递给其他函数，在特定事件发生时被调用
 *      解释：函数作为参数被传给其他函数，在需要时被其他函数在函数体内执行--回调
 */

int multiply(int a, int b, int c){
    return a*b*c;
}

typedef int (*pFunc1)(int, int, int);   //函数指针
using pFunc2 = int(*)(int, int, int);   //函数指针
using pFunc3 = int(int, int, int);  //函数类型别名

void test(){

    //C风格函数指针
    pFunc1 f = &multiply;
    cout << f(1,2,3) << "\n";

    //C++风格函数指针
    pFunc2 f2 = multiply;
    cout << f2(1,2,3) << "\n";

    //c++风格函数类型别名 + 指针使用
    pFunc3* f3 = multiply;
    cout << f3(1,2,3) << "\n";

    //C风格函数指针: 直接声明函数指针变量
    int (*f4)(int, int, int) = multiply;
    cout << f4(1,2,3) << "\n";

}

int main(){
    test();
    return 0;
}