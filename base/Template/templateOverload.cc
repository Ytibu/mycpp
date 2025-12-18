#include <iostream>
using std::cout;

/**函数模板重载：
 *      重载条件：@函数名相同；@模板参数数量不同；@返回值类型不同
 *      模板参数列表或函数参数列表（即签名）不同
 * 
 * 函数模板与普通函数重载：
 *      重载条件：@函数名相同；@函数参数列表相同；@返回值类型相同；
 *      重载规则(优先级)：精确匹配的普通函数 > 特化的函数模板 > 模板参数推导实例化的普通函数模板 > 类型转换可以匹配的普通函数
 */


// 版本1：一个模板参数
template <typename T>
void print(const T& value) {
    std::cout << "Version 1 (One Arg): " << value << std::endl;
}

// 版本2：两个模板参数
template <typename T1, typename T2>
void print(const T1& v1, const T2& v2) {
    std::cout << "Version 2 (Two Args): " << v1 << ", " << v2 << std::endl;
}

// 版本3：两个模板参数，函数参数类型不同(模板参数推导结果不同)
template <typename T1, typename T2>
void print(const T1 *v1,const T2 *v2) {
    std::cout << "Version 3 (Two Args): " << v1 << ", " << v2 << std::endl;
}


/*函数模板重载*/
void test(){

    const int x = 10;

    print(42);           // 调用版本1: print<int>
    print(3.14, "Hello"); // 调用版本2: print<double, const char*>
    print(&x, &x);  // 调用版本3: print<int*, int*>
}

//普通函数4与版本1重载
void print(const int& value){
    std::cout << "Version 4 (One Arg): " << value << std::endl;
}


/*函数模板与普通函数重载*/
void test1(){
    print(42);  //调用普通函数
    print(3.14);    //调用函数模板(模板产生更精确的匹配,也就是普通函数参数需要转换为int)
    print<>(3.14);  //调用函数模板(强制匹配模板函数，有<>必须调用模板函数)
    print<int>(42); //调用函数模板(强制匹配模板函数，由<>且指定参数类型，转换为int再调用模板函数)
}

int main() {
    test();
    test1();
    return 0;
}