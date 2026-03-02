#include "taskQueue.h"

#include <stdio.h>
#include <stdlib.h>


int taskQueueInit(taskQueue_t *pqueue)
{
    pqueue->pHead = NULL;  /*初始化头指针*/
    pqueue->pTail = NULL;  /*初始化尾指针*/
    pqueue->queueSize = 0; /*初始化队列大小*/
    return 0;
}

int enQueue(taskQueue_t *pqueue, int netFd)
{
    node_t *newNode = (node_t *)malloc(sizeof(node_t)); /*创建新节点*/
    newNode->netFd = netFd;                             /*设置节点的netFd*/
    if (pqueue->queueSize == 0)
    {                               /*如果队列为空*/
        pqueue->pHead = newNode;    /*设置头指针指向新节点*/
        pqueue->pTail = newNode;    /*设置尾指针指向新节点*/
    }
    else
    {                                   /*如果队列不为空*/
        pqueue->pTail->pNext = newNode; /*将新节点添加到队列尾部*/
        pqueue->pTail = newNode;        /*更新尾指针*/
    }
    ++pqueue->queueSize;

    return 0;
}

int deQueue(taskQueue_t *pqueue)
{
    node_t *pCur = pqueue->pHead; /*获取队列头节点*/
    pqueue->pHead = pCur->pNext; /*更新头指针指向下一个节点*/
    if(pqueue->queueSize == 1){   /*如果队列只有一个节点，更新尾指针为NULL*/
        pqueue->pTail = NULL;
    }
    free(pCur);   /*释放原头节点的内存*/
    --pqueue->queueSize;   /*更新队列大小*/

    return 0;
}