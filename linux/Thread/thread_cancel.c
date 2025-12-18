#include <Cfun.h>

/*
 *  线程取消：int pthread_cancel (pthread_t __th);   传入：拷贝线程id；返回：线程取消成功返回0，失败返回错误码
 * 
 * 调用线程取消函数后并不会立即取消线程，只有：线程发生系统调用 或 调用pthread_testcancel()
 * 注意：如果盲目的子线程取消，可能会导致子线程的资源无法释放，从而导致内存泄漏
 */


void thread_Func(void *arg)
{
    while(1)
    {
        printf("thread_Func\n");
        sleep(1);
    } 
}


/*
 * 线程资源清理：
 *      1.创建一个资源清理栈
 *      2.申请资源后压栈
 *      3.线程意外终止，清理栈弹出，释放资源
 *      4.主动释放资源，手动弹栈来释放资源
 */


int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_Func, NULL);
    sleep(2);
    pthread_cancel(tid);
    pthread_join(tid, NULL);
    return 0; 
}