#include "threadPool.h"

int threadPoolInit(threadPool_t *pthreadPool, int workerNum)
{
    initTidArr(&pthreadPool->tidArr, workerNum);    /*初始化线程ID数组*/

    taskQueueInit(&pthreadPool->taskQueue);         /*初始化任务队列*/

    pthread_mutex_init(&pthreadPool->mutex, NULL);  /*初始化互斥锁*/

    pthread_cond_init(&pthreadPool->cond, NULL);   /*初始化条件变量*/

    pthreadPool->exitFlag = 0;                      /*初始化退出标志*/
    
    return 0;
}