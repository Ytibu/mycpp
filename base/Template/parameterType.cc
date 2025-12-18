#include <iostream>
using std::cout;

/**模板参数类型与非参数类型
 *      优先级：指定的类型 > 推导出的类型 > 默认参数
 */

// 模板参数类型：类型参数
template <typename T>
T add1(T a, T b)
{
    return a + b;
}

// 模板参数类型：类型参数和非类型参数(只能是整型，浮点型不行)
template <typename T, int kBase>
T add2(T a, T b)
{
    return a + b + kBase;
}

// 模板参数类型：类型参数、非类型参数和默认参数(非类型参数可以赋默认值)
template <typename T, int kBase = 0>
T add3(T a, T b)
{
    return a + b + kBase;
}

// 模板参数类型：类型参数、非类型参数和默认参数
//(非类型参数可以赋默认值,参数类型也可赋默认参数，默认参数为类型)
template <typename T = int, int kBase = 0>
T add4(T a, T b)
{
    return a + b;
}

/*只有参数类型*/
void test()
{
    cout << add1(1, 2) << "\n";             // 自动推导
    cout << add1<>(1, 2) << "\n";           // 强制使用模板
    cout << add1<double>(1.1, 2.2) << "\n"; // 指定参数类型
}

/*参数类型和非类型参数*/
void test2()
{
    cout << add2<int, 3>(1, 2) << "\n";        // 指定非参数类型的值，同时还要指定参数类型的值
    cout << add2<double, 3>(1.1, 2.2) << "\n"; // 指定参数类型与非参数类型的值
}

void test3()
{
    cout << add3<int>(1, 2) << "\n";        // 指定参数类型的值，非参数类型使用默认值
    cout << add3<double>(1.1, 2.2) << "\n"; // 指定参数类型的值，非参数类型使用默认值
    cout << add3<int, 3>(1, 2) << "\n";     // 指定参数类型的值，指定非参数类型的值
}

void test4()
{
    cout << add4<>(1, 2) << "\n";           // 全部使用默认参数
    cout << add4<double>(1.1, 2.2) << "\n"; // 参数类型使用默认值，非参数类型使用默认值
    cout << add4<int, 3>(1, 2) << "\n";     // 参数类型使用指定值，非参数类型使用指定值
}

int main()
{
    test();
    test2();
    test3();
    test4();
    return 0;
}