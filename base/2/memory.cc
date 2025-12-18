#include <iostream>
using std::cout;

int g_number = 1;   //全局静态区
static int s_number = 2;

void test()
{
    int l_number = 3;   //栈区
    char str1[] = "hello";  //栈区
    // 增加堆区内存分配
    int* heap_int = new int(42);  //堆区
    char* heap_str = new char[10]; //堆区
    char* pstr2 = "world"; //文字常量区，只读
    
    // 打印栈区变量地址（栈区）
    printf("%-12s: %p\n", "str1", str1);
    printf("%-12s: %p\n", "l_number", &l_number);

    // 打印堆区变量地址（堆区）
    printf("%-12s: %p\n", "heap_int", heap_int);
    printf("%-12s: %p\n", "heap_str", heap_str);

    // 打印全局/静态变量地址（全局/静态区）
    printf("%-12s: %p\n", "s_number", &s_number);
    printf("%-12s: %p\n", "g_number", &g_number);
    
    // 文字常量区
    printf("%-12s: %p\n", "pstr2", pstr2);

    // 函数地址（程序代码区）
    printf("%-12s: %p\n", "test", test);

    // 释放堆区内存
    delete heap_int;
    delete[] heap_str;
} 

int main(){

    test();
    printf("%-12s: %p\n", "main", main);

}