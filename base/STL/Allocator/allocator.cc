#include <memory>
using std::allocator;

/**
 * 空间配置器: allocator
 * 特点：
 *      空间的申请和对象的构建严格分开
 * 频繁在堆空间开辟和回收：1.会产生内存碎片 2.new/delete的底层malloc/free需要进入内核态会存在系统开销
 */


/* Member functions 成员函数*/
void test(){

    /*申请原始的未初始空间： T* allocate(std::size_t n); */
    
    /* 释放空间：void deallocate(T* p, std::size_t n); */

    /* 在指定空间构建对象：void construct( pointer p, const_reference val ); */

    /* 销毁对象：void destroy( pointer p ); */
}


