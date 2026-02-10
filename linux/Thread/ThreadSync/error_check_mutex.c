#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

/* 使用 PTHREAD_MUTEX_ERRORCHECK_NP 类型的互斥锁---检错锁，检测错误的锁操作 */

int main(int argc, char *argv[])
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK_NP);

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, &attr);

    pthread_mutex_lock(&mutex);
    printf("lock once\n");

    int ret = pthread_mutex_lock(&mutex);
    if (ret != 0)
    {
        printf("lock twice error: %s\n", strerror(ret));
    }

    pthread_mutex_unlock(&mutex);
    printf("unlock once\n");

    ret = pthread_mutex_unlock(&mutex);
    if (ret != 0)
    {
        printf("unlock twice error: %s\n", strerror(ret));
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&attr);

    return 0;
}