#include <string.h>
#include <iostream>
using std::cout;

/**模板特化：对于某些特殊类型，使用不同的实现
 *      必须先存在基础的模板函数
 *      解决通用模板无法解决的问题
 */


template<typename T>
T add(T a, T b)
{
    return a + b;
}

template<>
const char *add<const char *>(const char *p1, const char *p2)
{
    char *ptemp = new char[strlen(p1) + strlen(p2) + 1]();
    strcpy(ptemp, p1);
    strcat(ptemp, p2);
    return ptemp;
}

int main()
{
    cout << add(1, 2) << std::endl;
    cout << add(1.1, 2.2) << std::endl;
    cout << add("hello", "world") << std::endl;
    return 0;
}