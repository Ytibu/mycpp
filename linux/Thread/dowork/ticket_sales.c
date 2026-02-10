#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

/**
 * 共享数据结构
 */
typedef struct Ticket_t
{
    int ticket_num;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Ticket;

/**
 * 卖票线程函数
 */
void *sell_Window(void *arg)
{
    Ticket *ticket = (Ticket *)arg;
    while (1)
    {
        pthread_mutex_lock(&ticket->mutex);
        while (ticket->ticket_num <= 0)
        {
            printf("没有票了，等待进货...\n");
            pthread_cond_wait(&ticket->cond, &ticket->mutex);
        }
        --ticket->ticket_num;
        printf("卖出一张票，剩余票数: %d\n", ticket->ticket_num);
        pthread_cond_signal(&ticket->cond);
        pthread_mutex_unlock(&ticket->mutex);

        usleep(100000);
    }

    pthread_exit(NULL);
}

/**
 * 进货线程函数
 */
void *stock_Window(void *arg)
{
    Ticket *ticket = (Ticket *)arg;
    while (1)
    {
        pthread_mutex_lock(&ticket->mutex);
        while (ticket->ticket_num >= 10)
        {
            printf("票已满，等待卖票...\n");
            pthread_cond_wait(&ticket->cond, &ticket->mutex);
        }
        ticket->ticket_num += 10;
        printf("补货 10 张，当前票数: %d\n", ticket->ticket_num);
        pthread_cond_signal(&ticket->cond);
        pthread_mutex_unlock(&ticket->mutex);

        usleep(200000);
    }

    pthread_exit(NULL);
}

/**
 * 多线程实现售票系统，通过条件变量和互斥锁来实现线程间的同步和互斥，保证售票系统的正确性和效率。
 */
int main(int argc, char *argv[])
{
    Ticket ticket;
    ticket.ticket_num = 10;
    pthread_mutex_init(&ticket.mutex, NULL);
    pthread_cond_init(&ticket.cond, NULL);

    pthread_t seller_thread1, seller_thread2, stocker_thread;
    pthread_create(&seller_thread1, NULL, sell_Window, &ticket);
    pthread_create(&seller_thread2, NULL, sell_Window, &ticket);
    pthread_create(&stocker_thread, NULL, stock_Window, &ticket);

    pthread_join(seller_thread1, NULL);
    pthread_join(seller_thread2, NULL);
    pthread_join(stocker_thread, NULL);

    pthread_mutex_destroy(&ticket.mutex);
    pthread_cond_destroy(&ticket.cond);

    return 0;
}