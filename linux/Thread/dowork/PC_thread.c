#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

/**
 * 利用链表实现一个队列
 * 创建共享资源，并初始化条件变量和互斥锁
 * 基于互斥锁和条件变量，根据共享资源的多少情况，生产者和消费者广播提醒其他线程
 * 实现队列的生产者消费者模型
 */

/**
 * @brief 定义队列节点结构体
 * 
 */
typedef struct Node
{
    int value;
    struct Node *next;
} Node;


/**
 * @brief 定义队列结构体
 * 
 */
typedef struct Queue
{
    Node *front;
    Node *rear;
    int size;
} Queue;



/**
 * @brief 入队
 * 
 * @param queue 
 * @param value 
 * @return int 
 */
int pushQueue(Queue *queue, int value)
{
    // Node *node = (Node *)malloc(sizeof(Node));
    Node *newNode = (Node *)calloc(1, sizeof(Node));
    newNode->value = value;
    if (queue->size == 0)
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    ++queue->size;

    return 0;
}


/**
 * @brief 出队
 * 
 * @param queue 
 * @return int 
 */
int popQueue(Queue *queue)
{
    if (queue->size == 0)
    {
        return -1;
    }

    Node *delNode = queue->front;
    queue->front = queue->front->next;
    if (queue->size == 1)
    {
        queue->rear = NULL;
    }
    free(delNode);
    --queue->size;

    return 0;
}


/**
 * @brief 遍历输出队列元素
 * 
 * @param queue 
 * @return int 
 */
int printQueue(Queue *queue)
{
    if (queue->size == 0)
    {
        printf("Queue is empty\n");
        return 0;
    }
    Node *curr = queue->front;
    while (curr != NULL)
    {
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
    return 0;
}

// 单元测试函数
void test()
{
    Queue myQueue;
    memset(&myQueue, 0, sizeof(myQueue));
    for (int i = 0; i < 10; ++i)
    {
        int value = rand() % 1000;
        pushQueue(&myQueue, value);
        printf("data = %d\n", value);
        printQueue(&myQueue);
    }
    printf("-----------------------\n");
    for (int i = 0; i < 10; ++i)
    {
        int frontVal = myQueue.front->value;
        popQueue(&myQueue);
        printf("front = %d\n", frontVal);
        printQueue(&myQueue);
    }
    for (int i = 0; i < 10; ++i)
    {
        int value = rand() % 1000;
        pushQueue(&myQueue, value);
        printf("data = %d\n", value);
        printQueue(&myQueue);
    }
}

/**
 * @brief 定义共享资源结构体
 * 
 */
typedef struct SharedContext
{
    Queue queue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} SharedContext;


/**
 * @brief 生产者线程函数
 * 
 * @param arg 
 * @return void* 
 */
void *Producer_Thread(void *arg)
{
    SharedContext *context = (SharedContext *)arg;
    while (1)
    {
        pthread_mutex_lock(&context->mutex);
        while (context->queue.size >= 10)
        {
            pthread_cond_wait(&context->cond, &context->mutex);
        }
        int value = rand() % 1000;
        pushQueue(&context->queue, value);
        printQueue(&context->queue);

        pthread_cond_broadcast(&context->cond);
        pthread_mutex_unlock(&context->mutex);
        sleep(3);
    }

    pthread_exit(NULL);
}


/**
 * @brief 消费者线程函数
 * 
 * @param arg 
 * @return void* 
 */
void *Consumer_Thread(void *arg)
{
    SharedContext *context = (SharedContext *)arg;
    while (1)
    {

        pthread_mutex_lock(&context->mutex);
        while (context->queue.size <= 1)
        {
            pthread_cond_wait(&context->cond, &context->mutex);
        }
        popQueue(&context->queue);
        printQueue(&context->queue);

        pthread_cond_broadcast(&context->cond);
        pthread_mutex_unlock(&context->mutex);
        sleep(1);
    }

    pthread_exit(NULL);
}


/* 生产者和消费者对于队列资源的处理 */
int main()
{
    SharedContext context;
    pthread_mutex_init(&context.mutex, NULL);
    pthread_cond_init(&context.cond, NULL);
    memset(&context.queue, 0, sizeof(context.queue));
    for (int i = 0; i < 8; ++i)
    {
        //int value = rand() % 1000;
        pushQueue(&context.queue, i);
        //printf("data = %d\n", value);
        printQueue(&context.queue);
    }
    printf("-----------------------\n");

    pthread_t Producer1, Producer2, Producer3, Consumer1, Consumer2, Consumer3;
    pthread_create(&Producer1, NULL, Producer_Thread, &context);
    pthread_create(&Producer2, NULL, Producer_Thread, &context);
    pthread_create(&Producer3, NULL, Producer_Thread, &context);

    pthread_create(&Consumer1, NULL, Consumer_Thread, &context);
    pthread_create(&Consumer2, NULL, Consumer_Thread, &context);
    // pthread_create(&Consumer3, NULL, Consumer_Thread, &context);
    pthread_join(Producer1, NULL);
    pthread_join(Producer2, NULL);
    pthread_join(Producer3, NULL);
    
    pthread_join(Consumer1, NULL);
    pthread_join(Consumer2, NULL);
    // pthread_join(Consumer3, NULL);

    return 0;
}