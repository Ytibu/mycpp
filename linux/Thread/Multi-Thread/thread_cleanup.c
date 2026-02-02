#include <Cfun.h>

/**
 * 线程资源清理步骤：
 *      1.创建一个资源清理栈
 *      2.申请资源后压栈
 *      3.线程意外终止，清理栈弹出，释放资源
 *      4.主动释放资源，手动弹栈来释放资源
 * 
 *      void pthread_cleanup_push(void (*routine)(void *),  void *arg); //将申请的资源进栈
 *      void pthread_cleanup_pop(int execute);  //将申请的资源手动弹栈，参数为1，则执行资源释放函数，为0则不执行资源释放函数
 * 注意：必须在同一个作用域成对出现，详见push_pop两个函数的宏定义
 *
 * 必须确保申请资源后将资源进栈，在此之后退出线程都可以释放资源。
 * 资源一旦进入栈中，不论何时退出线程，栈中的资源都会被释放。
 * 手动调用资源释放函数，替换成，手动调用弹栈函数
 */


void cleanup_1(void *arg)
{
    int *p = (int *)arg;
    printf("cleanup_func1\n");
    free(p);
}

void cleanup_2(void *arg)
{
    int *p = (int *)arg;
    printf("cleanup_func2\n");
    free(p);
}

void cleanup_3(void *arg)
{
    int *pFd = (int *)arg;
    printf("cleanup_func3\n");
    close(*pFd);
}

void *thread_func(void *arg)
{

    // pthread_exit(NULL); //未申请资源 -- 不存在内存泄漏
    int *p1 = (int *)malloc(sizeof(int));
    pthread_cleanup_push(cleanup_1, p1);


    int *p2 = (int *)malloc(sizeof(int));
    // pthread_exit(NULL);   //未进栈--不会释放资源
    pthread_cleanup_push(cleanup_2, p2);


    int fd = open("test.txt", O_RDONLY);
    pthread_cleanup_push(cleanup_3, &fd);
    // pthread_exit(NULL); //进栈--会释放资源


    printf("thread_func\n");

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    // pthread_exit(NULL);   //手动弹栈释放资源 -- 即使在此之前退出，但是系统会自动弹栈
    pthread_cleanup_pop(1);

    //return NULL;  //尽量不使用return，return如果提前退出线程，系统不会自动弹栈
    printf("------------------------------------------------------\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_join(tid, NULL);
    return 0;
}