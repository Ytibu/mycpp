#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <pthread.h>
#include "worker.h"
#include "taskQueue.h"

/* 
    记录所有子线程信息
    任务队列
    锁
    条件变量
 */
typedef struct threadPool_s{
    tidArr_t tidArr;        //子线程信息
    int exitFlag;
    taskQueue_t taskQueue;  //任务队列
    pthread_mutex_t mutex;  //互斥锁
    pthread_cond_t cond;    //条件变量
} threadPool_t;

/* 根据传入的线程池结构体，初始化基本变量 */
int threadPoolInit(threadPool_t *pthreadPool, int workerNum);

#endif