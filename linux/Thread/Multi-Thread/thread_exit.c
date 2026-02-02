#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


/**
 * void pthread_exit (void *__retval);
 *  线程退出：终止调用线程的执行，并返回一个指针作为线程的返回值
 *  注意：调用此函数不会终止进程，只会终止调用线程的执行
 */

void *thread_Func()
{
    printf("thread_Func\n");

    pthread_exit(NULL);
    printf("after pthread_exit\n");
}

int main()
{

    pthread_t thread;
    pthread_create(&thread, NULL, thread_Func, NULL);
    printf("main thread\n");
    while(1){
        sleep(1);
    }
    pthread_join(thread, NULL);
}