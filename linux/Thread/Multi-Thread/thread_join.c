#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/**
 * int pthread_join (pthread_t __th, void **__thread_return);
 *    参数1：线程id的拷贝
 *    参数2：用于接收线程退出时的返回值
 *    返回值：成功返回0，失败返回错误码
 * 
 * 等待并回收一个已经终止的线程，回收后释放线程资源。
 * 如果线程已经终止，则立即回收线程资源并获取线程的返回值。
 * 如果线程没有终止，则调用线程会阻塞，直到被等待的线程终止。
 * 注意：不能对同一个线程调用两次pthread_join，否则会导致程序崩溃。
 */


void *thread_Func(){
    printf("thread_Func\n");

    pthread_exit((void *)123);
}

int main(){

    pthread_t threadId;
    pthread_create(&threadId, NULL, thread_Func, NULL);

    void *retval;
    pthread_join(threadId, &retval);
    
    printf("ret = %ld\n", (long)retval);
    
    return 0;
}