#include <Cfun.h>

/*
 *  线程取消：int pthread_cancel (pthread_t __th);   传入：拷贝线程id；返回：线程取消成功返回0，失败返回错误码
 * 
 * 调用线程取消函数后并不会立即取消线程，只有：线程发生系统调用 或 调用pthread_testcancel()
 * 
 *      注意：如果盲目的子线程取消，可能会导致子线程的资源无法释放，从而导致内存泄漏
 */


void *thread_Func(void *arg)
{
    while(1)
    {
        printf("thread_Func\n");
        //pthread_testcancel();   // 设置取消点，遇到取消点时，线程会被取消
    }

    pthread_exit(NULL);
}


int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_Func, NULL);

    sleep(1);
    printf("will cancel the thread\n");
    pthread_cancel(tid);    // 取消线程，并不会立即取消，而是在遇到取消点时取消
    void *retval;
    pthread_join(tid, &retval);
    printf("ret = %ld\n", (long)retval);

    return 0;
}