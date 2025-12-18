#include <head.h>

/**
 * 在头文件中使用此方法，可以确保extern "C" {}中的代码不论环境都按照c的方式进行编译调用
 */

#ifndef _cplusplus
extern "C"
{
#endif

int add(int a, double b)    //此代码不论环境都按照c的方式编译方式进行调用
{
    return a + b;
}

#ifndef _cplusplus
}
#endif
