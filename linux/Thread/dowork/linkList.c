#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * 项目核心功能：父进程创建一个完整的链表并创建子线程，子线程遍历该链表并打印每个节点的数据
 */


 /**
  * @brief 链表节点结构体定义
  * 
  */
typedef struct node_s
{
    int data;
    struct node_s *pNext;
} node_t;


/**
 * @brief 结构体定义：链表
 * 
 */
typedef struct linklist_s
{
    node_t *pHead;
    node_t *pTail;
} linklist_t;


/**
 * 头插法创建链表
 */

/**
 * @brief 头插法创建链表
 * 
 * @param ppHead 
 * @param ppTail 
 * @param value 
 */
void headInsert(node_t **ppHead, node_t **ppTail, int value)
{
    node_t *pNew = (node_t *)malloc(sizeof(node_t));
    memset(pNew, 0, sizeof(node_t));
    pNew->data = value;

    if (*ppHead == NULL)
    {
        *ppHead = pNew;
        *ppTail = pNew;
    }
    else
    {
        pNew->pNext = *ppHead;
        *ppHead = pNew;
    }
}



/**
 * @brief 尾插法创建链表
 * 
 * @param ppHead 
 * @param ppTail 
 * @param value 
 */
void tailInsert(node_t **ppHead, node_t **ppTail, int value)
{
    node_t *pNew = (node_t *)malloc(sizeof(node_t));
    memset(pNew, 0, sizeof(node_t));
    pNew->data = value;
    if (*ppHead == NULL)
    {
        *ppHead = pNew;
        *ppTail = pNew;
    }
    else
    {
        (*ppTail)->pNext = pNew;
        *ppTail = pNew;
    }
}

/**
 * @brief 遍历链表
 * 
 * @param pHead 
 */
void visitList(node_t *pHead)
{
    node_t *pCur = pHead;
    while (pCur != NULL)
    {
        printf("%d ", pCur->data);
        pCur = pCur->pNext;
    }
    printf("\n");
}

/**
 * @brief 单元测试
 * 
 */
void unitTest(){
    node_t *pHead = NULL;
    node_t *pTail = NULL;

    printf("headInsert list:\n");
    for(int i = 0; i < 5; ++i)
    {
        headInsert(&pHead, &pTail, i);
        visitList(pHead);
    }

    printf("tailInsert list:\n");
    for(int i = 5; i < 10; ++i)
    {
        tailInsert(&pHead, &pTail, i);

        visitList(pHead);
    }
}

void *thread_function(void *arg)
{
    linklist_t *pList = (linklist_t *)arg;
    printf("Thread: Visiting List:\n");
    visitList(pList->pHead);
    return NULL;
}

int main(int argc, char *argv[])
{
    linklist_t list;
    memset(&list, 0, sizeof(linklist_t));
    list.pHead = NULL;
    list.pTail = NULL;
    
    for(int i = 0; i < 10; ++i)
    {
        tailInsert(&list.pHead, &list.pTail, i);
    }

    pthread_t threadId;
    pthread_create(&threadId, NULL, thread_function, &list);
    pthread_join(threadId, NULL); // 等待线程结束

    return 0;
}