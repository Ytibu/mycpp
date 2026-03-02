#ifndef __WORKER_H__
#define __WORKER_H__

#include <pthread.h>

// 前置声明（避免此处找不到 threadPool_t）
typedef struct threadPool_s threadPool_t;

// 线程池信息结构体
typedef struct tidArr_s{
    pthread_t *Arr;
    int workerNum;
} tidArr_t;


int initTidArr(tidArr_t *ptidArr, int workerNum);   /* 初始化线程池信息结构体*/
int makeWorker(threadPool_t *pthreadPool);  /* 根据线程池信息创建线程池*/
void* threadFunc(void *arg);   /* 子线程入口函数*/

#endif