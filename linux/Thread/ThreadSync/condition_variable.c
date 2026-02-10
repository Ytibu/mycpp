#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define _MUM__ 50

/**
 * 条件变量：Condition Variable
 *
 *      int pthread_cond_init (pthread_cond_t * __cond, const pthread_condattr_t * __cond_attr) //初始化条件变量
 *      int pthread_cond_wait (pthread_cond_t * __cond,  pthread_mutex_t * __mutex) //等待条件变量满足
 *      int pthread_cond_signal (pthread_cond_t *__cond)    //唤醒一个等待条件变量的线程
 *      int pthread_cond_broadcast (pthread_cond_t *__cond)   //唤醒所有等待条件变量的线程
 *      int pthread_cond_destroy (pthread_cond_t * __cond)   //销毁条件变量
 *
 * wait底层逻辑：进入阻塞前解锁，等待条件变量，如果条件变量满足则解除阻塞，并返回，否则阻塞。
 */

/**
 * 利用条件变量实现两个线程顺序并发执行
 */

struct shared_data
{
    int flag;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};
struct shared_data sd;

void pthread_func1(void *arg)
{
    pthread_mutex_lock(&sd.mutex);
    while(sd.flag != 0)
    {
        pthread_cond_wait(&sd.cond, &sd.mutex);
    }
    printf("this is thread1\n");

    sd.flag = 1;
    pthread_cond_signal(&sd.cond);
    pthread_mutex_unlock(&sd.mutex);

    pthread_exit(NULL);
}

void *pthread_func2(void *arg)
{
    pthread_mutex_lock(&sd.mutex);
    while(sd.flag != 1)
    {
        pthread_cond_wait(&sd.cond, &sd.mutex);
    }
    printf("this is thread2\n");

    sd.flag = 0;
    pthread_cond_signal(&sd.cond);
    pthread_mutex_unlock(&sd.mutex);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    pthread_cond_init(&sd.cond, NULL);
    pthread_mutex_init(&sd.mutex, NULL);
    sd.flag = 1;

    int ret1 = pthread_create(&t1, NULL, &pthread_func1, NULL);
    if (ret1 != 0)
    {
        fprintf(stderr, "pthread_create t1 failed: %s\n", strerror(ret1));
        return -1;
    }

    int ret2 = pthread_create(&t2, NULL, &pthread_func2, NULL);
    if (ret2 != 0)
    {
        fprintf(stderr, "pthread_create t2 failed: %s\n", strerror(ret2));
        return -1;
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_cond_destroy(&sd.cond);
    pthread_mutex_destroy(&sd.mutex);

    return 0;
}