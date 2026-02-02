#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * 多线程数据管理示例
 * 演示全局数据、栈空间数据和堆空间数据在多线程中的使用和管理
 * 
 * 父子线程之间共享整个进程的地址空间：全局变量和静态变量、堆空间数据、文件描述符表是共享的
 * 但是每个线程有自己的栈空间，栈空间数据在线程之间是不共享的
 * 
 * 注意：可以通过传参使得子进程和父进程可以操作同一片数据，但是需要注意线程同步问题
 */

typedef struct{
    int *global_data; // 指向全局数据
    int *stack_data;  // 指向栈空间数据
    int *heap_data;   // 指向堆空间数据
} thread_args_t;

int global_data = 100; // 全局数据，所有线程共享

void *thread_function(void *arg)
{
    thread_args_t *args = (thread_args_t *)arg;
    
    // 线程可以通过指针访问和修改主线程的数据
    printf("Thread: Global Data: %d\n", *(args->global_data));
    printf("Thread: Stack Data: %d\n", *(args->stack_data));
    printf("Thread: Heap Data: %d\n", *(args->heap_data));

    ++(*(args->global_data)); // 修改全局数据
    ++(*(args->stack_data));  // 修改栈空间数据
    ++(*(args->heap_data));   // 修改堆空间数据

    return NULL;
}

int main(int argc, char *argv[])
{
    int stack_data = 200; // 栈空间数据
    int *heap_data = malloc(sizeof(int));
    *heap_data = 300;     // 堆空间数据

    thread_args_t *args = malloc(sizeof(thread_args_t));
    args->global_data = &global_data; // 传递全局数据地址
    args->stack_data = &stack_data;   // 传递栈空间数据地址
    args->heap_data = heap_data;      // 传递堆空间数据地址

    pthread_t threadId;
    pthread_create(&threadId, NULL, thread_function, args);
    pthread_join(threadId, NULL); // 等待线程结束

    printf("After Thread Execution:\n");
    printf("Main: Global Data: %d\n", global_data); // 全局数据
    printf("Main: Stack Data: %d\n", stack_data);    // 栈空间数据
    printf("Main: Heap Data: %d\n", *heap_data);     // 堆空间数据

    free(args);      // 释放分配的内存
    free(heap_data); // 释放分配的内存
    return 0;
}