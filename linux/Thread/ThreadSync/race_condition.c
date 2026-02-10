#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define _NUM_ 1000000

/**
 * 竞争条件：多个线程或进程并发访问共享资源时，程序的执行结果依赖于线程执行的相对时间顺序，从而可能导致不可预测或错误的行为。
 */

void* thread_Func(void *arg){
    
    int *val = (int *)arg;
    for(int i = 0; i < _NUM_; ++i){
        // 临界资源
        ++(*val);
    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    pthread_t t1;
    int val = 0;

    pthread_create(&t1, NULL, thread_Func, &val);
    for(int i = 0; i < _NUM_; ++i){
        ++val;
    }

    pthread_join(t1, NULL);
    printf("val = %d\n", val);

    return 0;
}