#include <iostream>

/**
 * 可变模板参数
 */


 /*递归解包的出口函数*/
void print(){
    std::cout << "\n";
}
template<typename T, typename... Args>
void print(const T  &firstArg, const Args... args)
{
    std::cout << firstArg << ' ';
    print(args...);
}



int sum(int firstArg){
    return firstArg;
}
template<typename T, typename... Args>
int sum(T firstArg, Args... args)
{
    return firstArg + sum(args...);
}

int main()
{
    print(1, 2.5, "hello", "world");
    int num = sum(1, 2, 3, 4, 5);
    std::cout << num << "\n";
    return 0;
}