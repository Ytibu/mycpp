#include <iostream>
#include <functional>

using std::cout;
using std::bind;
using std::function;
using namespace std::placeholders;

/**
 * 头文件：<functional>
 * 函数绑定:std::bind()
 * bind语句中的参数顺序就是函数形参中的顺序，但是其中的占位符数字代表实参中的第几个参数代表占位符本身
 *      回调函数的执行参数数量可以远大于函数的参数数量
 *      即：bind()语句中的参数严格对应于函数中的形参，bind()语句中的占位符数字对应于调用函数的语句中的实参
 */

class Example{
public:
    int sub(int a, int b){
        return a - b;
    }
    int data = 100;
};


int sub(int a, int b){
    return a - b;
}

int multiply(int a, int b, int &c){
    return a * b * c;
}

void putIt(int i, int j, const std::string &s, double d){
    cout << i << " " << j << " " << s << " " << d << std::endl;
}

/* 函数绑定： std::bind()*/
void test(){
    cout << "函数绑定" << std::endl;

    auto f = std::bind(sub, 1, 2);
    std::cout << f() << std::endl;

    auto f2 = std::bind(multiply, 1, 2, 3);
    std::cout << f2() << std::endl;

    Example ex;
    auto f3 = std::bind(&Example::sub, &ex, 1, 2);
    std::cout << f3() << std::endl;

}

/* 参数占位符 */
void test1(){
    cout << "参数占位符" << std::endl;

    using namespace std::placeholders;
    auto f1 = std::bind(putIt, _1, _2, _3, _4); //占位符代表形参中的参数位置 
    auto f2 = std::bind(putIt, 10, _1, _2, _3); //占位符中的数字代表实参中的参数位置
    auto f3 = std::bind(putIt, 10, _2, _1, _3);
    f1(1, 2, "hello", 4);
    f2(1, "hello", 4.1);
    f3("hello",1,3.3,4,5,5);

}

/* std::function */
void test2(){
    cout << "std::function" << std::endl;

    function<int()> f1 = std::bind(sub, 1, 2);
    std::cout << f1() << std::endl;

    function<int()> f2 = std::bind(multiply, 1, 2, 3);
    std::cout << f2() << std::endl;
}

/* 引用包装器 */
void test3(){
    cout << "引用包装器" << std::endl;

    //引用传递：如果函数传入参数为引用，使用std::ref()；如果传入参数时const引用，使用std::cref()
    int number = 100;
    function<int(int,int)> f1 = std::bind(multiply, _1, _2, std::ref(number));
    std::cout << f1(1,2) << std::endl;
    std::cout << number << std::endl;
}


/* 函数对象的综合使用 */
void test4(){
    cout << "函数对象综合使用" << std::endl;

    Example ex1;
    function<int()> f1 = std::bind(&Example::sub, &ex1, 1, 2);
    std::cout << f1() << std::endl;

    //绑定函数multiply，回调函数的调用参数为<int(int,int)> -- 返回int 传入int int int(只是代表调用函数的形式)
    function<int(int,int)> f2 = std::bind(multiply, _2,_1,100);
    std::cout << f2(2,1) << std::endl;

    Example ex2;
    function<int(int,int)> f3 = std::bind(&Example::data, &ex2);
    std::cout << f3(1,1) << std::endl;

    Example ex3;
    function<int(int,int,int)> f4 = std::bind(&Example::sub, &ex3, 100, _3);//bind()语句中的参数个数只能于形参一致
    //function<int(int,int)>的参数类型与调用的函数一致
    std::cout << f4(0,0,3) << std::endl;
}

void test5(){
    cout << "函数对象综合使用" << std::endl;

    Example ex1;

    //对象的地址
    function<int()> f1 = std::bind(&Example::sub, &ex1, 1, 2);
    std::cout << f1() << std::endl;

    //拷贝对象
    function<int()> f2 = std::bind(&Example::sub, ex1, 1, 2);
    std::cout << f2() << std::endl;

}



int main(){
    test();
    test1();
    test2();
    test3();
    test4();
    return 0;
}