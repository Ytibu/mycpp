#include <Cfun.h>

/**
 * 实现队列的生产者消费者模型
 */

typedef struct Node
{
    int data_t;
    struct Node *next_t;
} mNode;

typedef struct Queue
{
    struct Node *front_t;
    struct Node *rear_t;
    int size_t;
} mQueue;

int pushQueue(mQueue *queue, int data)
{
    mNode *node = (mNode *)malloc(sizeof(mNode));
    node->data_t = data;
    if (queue->size_t == 0)
    {
        queue->front_t = node;
        queue->rear_t = node;
    }
    else
    {
        queue->rear_t->next_t = node;
        queue->rear_t = node;
    }
    ++queue->size_t;

    return 0;
}

int popQueue(mQueue *queue)
{
    if (queue->size_t == 0)
    {
        return -1;
    }

    mNode *del = queue->front_t;
    queue->front_t = queue->front_t->next_t;
    if (queue->size_t == 1)
    {
        queue->rear_t = NULL;
    }
    free(del);
    --queue->size_t;

    return 0;
}

int visitQueue(mQueue *queue)
{
    if (queue->size_t == 0)
    {
        printf("Queue is empty\n");
        return 0;
    }
    mNode *node = queue->front_t;
    while (node != NULL)
    {
        printf("%d ", node->data_t);
        node = node->next_t;
    }
    printf("\n");
    return 0;
}

// 单元测试函数
void test()
{
    mQueue myQueue;
    memset(&myQueue, 0, sizeof(myQueue));
    for (int i = 0; i < 10; ++i)
    {
        int data = rand() % 1000;
        pushQueue(&myQueue, data);
        printf("data = %d\n", data);
        visitQueue(&myQueue);
    }
    printf("-----------------------\n");
    for (int i = 0; i < 10; ++i)
    {
        int front = myQueue.front_t->data_t;
        popQueue(&myQueue);
        printf("front = %d\n", front);
        visitQueue(&myQueue);
    }
    for (int i = 0; i < 10; ++i)
    {
        int data = rand() % 1000;
        pushQueue(&myQueue, data);
        printf("data = %d\n", data);
        visitQueue(&myQueue);
    }
}

void *Producer_Thread(void *arg)
{
    pthread_exit(NULL);
}

void *Consumer_Thread(void *arg)
{
    pthread_exit(NULL);
}

int main()
{
    test();
    pthread_t Producer, Consumer;
    pthread_create(&Producer, NULL, Producer_Thread, NULL);
    pthread_create(&Consumer, NULL, Consumer_Thread, NULL);
    pthread_join(Producer, NULL);
    pthread_join(Consumer, NULL);
    return 0;
}