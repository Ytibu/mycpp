#include "MyTemplate"

template <typename T>
void print(const T &t)
{
    std::cout << t << std::endl;
}

//模板的实现文件name.tcc直接引入模板头文件name