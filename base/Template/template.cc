#include <iostream>
#include <string>
using std::cout;
using std::string;

/**
 * 模板：template<typename T> or template<class T>    函数模板，类模板
 * 实现过程：函数模板 --> 生成相应的模板函数 --> 编译 --> 链接 --> 生成exe
 */

template <typename T>
T add(T a, T b){
    return a + b;
}

template <typename T1, typename T2>
T1 add(T1 a, T2 b){
    return a + b;
}

/*模板实例化*/
void test()
{
    cout << add(1, 2) << " "; // 自动推导(隐式模板参数)
    cout << add(1.1, 2.2) << '\n';

    cout << add<int>(1, 2) << "  "; // 显式模板参数
    cout << add<double>(1.5, 2.1) << '\n';

    /*此处会先将参数隐式转换成指定的类型，然后使用指定的类型运行函数*/
    cout << add<int>(1.5, 2.1) << " ";
    cout << add<double>(1, 2) << " ";
    cout << add<int>(1, 2.2) << " ";
    cout << add<double>(1.5, 2) << '\n';
    // cout << add<char>("a", "b") << '\n';//error: 模板参数错误，不匹配
}

int main()
{
    test();
}