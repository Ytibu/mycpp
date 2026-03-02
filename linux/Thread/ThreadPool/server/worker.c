#include "worker.h"

#include "threadPool.h"
#include "transFile.h"

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

int initTidArr(tidArr_t *ptidArr, int workerNum)
{
    ptidArr->Arr = (pthread_t *)calloc(workerNum, sizeof(pthread_t));   /*申请内存*/
    ptidArr->workerNum = workerNum;   /*记录线程数量*/
    return 0;
}

void unlock(void *arg)
{
    threadPool_t *pthreadPool = (threadPool_t *)arg;
    printf("unlock\n");
    pthread_mutex_unlock(&pthreadPool->mutex);   /*解锁*/
}


int makeWorker(threadPool_t *pthreadPool)
{
    for (int i = 0; i < pthreadPool->tidArr.workerNum; i++) {
        pthread_create(&pthreadPool->tidArr.Arr[i], NULL, threadFunc, (void *)pthreadPool);   /*创建子线程*/
    }
    return 0;
}


void* threadFunc(void *arg)
{
    threadPool_t *pthreadPool = (threadPool_t *)arg;
    
    while(1){
        int netfd;
        pthread_mutex_lock(&pthreadPool->mutex);
        //pthread_cleanup_push(unlock, (void *)pthreadPool);   /*注册清理函数*/
        while(pthreadPool->exitFlag == 0 && pthreadPool->taskQueue.queueSize <= 0){    /*如果任务队列为空，等待条件变量*/
            pthread_cond_wait(&pthreadPool->cond, &pthreadPool->mutex);    /*等待条件变量*/
        }
        if(pthreadPool->exitFlag == 1){   /*如果退出标志为1，说明有退出信号，退出线程*/
            pthread_mutex_unlock(&pthreadPool->mutex);   /*解锁*/
            printf("worker thread %lu exiting...\n", pthread_self());
            pthread_exit(NULL);
        }
        netfd = pthreadPool->taskQueue.pHead->netFd;   /*获取任务队列头节点的netFd*/
        // 从任务队列中取出一个任务
        deQueue(&pthreadPool->taskQueue);   /*从任务队列中取出一个任务*/
        pthread_mutex_unlock(&pthreadPool->mutex);
        //pthread_cleanup_pop(1);   /*取消注册清理函数*/

        // TODO: 执行任务
        transFile(netfd);   /*执行任务*/
        close(netfd);
    }
}