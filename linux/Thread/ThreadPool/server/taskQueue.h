#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

// 队列中的节点
typedef struct node_s {
    int netFd;
    struct node_s *pNext;
} node_t;

// 队列
typedef struct taskQueue_s{
    node_t *pHead;
    node_t *pTail;
    int queueSize;
}taskQueue_t;

int taskQueueInit(taskQueue_t *pqueue);
int enQueue(taskQueue_t *pqueue, int netFd);
int deQueue(taskQueue_t *pqueue);

#endif