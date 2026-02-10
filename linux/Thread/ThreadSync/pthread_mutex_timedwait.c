#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

/**
 * 带超时的条件变量等待：pthread_cond_timedwait
 *
 *      int pthread_cond_timedwait (pthread_cond_t * __cond,
 *                                  pthread_mutex_t * __mutex,
 *                                  const struct timespec * __abstime)
 *
 * 功能：与pthread_cond_wait类似，但多了一个超时参数abstime，表示绝对时间。
 *      如果在指定时间内条件变量没有被满足，则解除阻塞并返回ETIMEDOUT错误码。
 *
 * 注意：abstime是绝对时间，而不是相对时间。
 */

int main(int argc, char *argv[])
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_mutex_lock(&mutex);
    struct timeval now;
    gettimeofday(&now, NULL);
    printf("now sec: %ld, now usec: %ld\n", now.tv_sec, now.tv_usec);

    struct timespec abstime;
    abstime.tv_sec = now.tv_sec + 5;
    abstime.tv_nsec = 0;

    int ret = pthread_cond_timedwait(&cond, &mutex, &abstime);
    // if (ret != 0){
    //     fprintf(stderr, "pthread_create t2 failed: %s\n", strerror(ret));
    // }
    gettimeofday(&now, NULL);
    printf("now sec: %ld, now usec: %ld\n", now.tv_sec, now.tv_usec);

    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}