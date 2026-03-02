#include "threadPool.h"
#include "worker.h"
#include "taskQueue.h"
#include "tcpInit.h"
#include "epoll.h"
#include "errorSet.h"

#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

int exitPipe[2];
void handler(int signum)
{
    printf("signum = %d\n", signum);
    write(exitPipe[1], "1", 1); /*向管道写入数据，通知子线程退出*/
}

// ./server 0.0.0.0 1234 3
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 4, "argc error"); /*参数检验*/

    pipe(exitPipe);
    if(fork() != 0){
        close(exitPipe[0]);
        
        signal(SIGUSR1, handler);
        wait(NULL);
        printf("main process exited\n");

        exit(0);
    }

    close(exitPipe[1]);

    threadPool_t pthreadPool;
    threadPoolInit(&pthreadPool, atoi(argv[3])); /*初始化线程池*/
    makeWorker(&pthreadPool);                    /*创建子线程*/

    int sockfd;
    tcpInit(argv[1], atoi(argv[2]), &sockfd); /*初始化TCP服务器*/

    int epfd = epoll_create(1);
    epollAdd(epfd, sockfd); /*将监听套接字添加到epoll中*/
    epollAdd(epfd, exitPipe[0]); /*将管道读端添加到epoll中*/

    while (1)
    {
        struct epoll_event readySet[1024];
        int readyNum = epoll_wait(epfd, readySet, 1024, -1); /*等待就绪事件*/

        for (int i = 0; i < readyNum; ++i)
        {
            if (readySet[i].data.fd == sockfd)
            {                                           /*监听套接字就绪，说明有新连接*/
                int newFd = accept(sockfd, NULL, NULL); /*接受新连接*/
                printf("get new client, netFd = %d!\n", newFd);
                pthread_mutex_lock(&pthreadPool.mutex);
                enQueue(&pthreadPool.taskQueue, newFd); /*将新连接添加到任务队列中*/
                pthread_mutex_unlock(&pthreadPool.mutex);
                pthread_cond_signal(&pthreadPool.cond); /*唤醒子线程*/
            }
            else if(readySet[i].data.fd == exitPipe[0])
            { /*管道读端就绪，说明有退出信号*/
                printf("get exit signal, exiting...\n");
                // for(int j = 0; j < pthreadPool.tidArr.workerNum; ++j){
                //     pthread_cancel(pthreadPool.tidArr.Arr[j]); /*取消子线程*/
                // }
                pthread_mutex_lock(&pthreadPool.mutex);
                pthreadPool.exitFlag = 1; /*设置退出标志，通知子线程退出*/
                pthread_mutex_unlock(&pthreadPool.mutex);
                pthread_cond_broadcast(&pthreadPool.cond); /*唤醒所有子线程*/

                for(int j = 0; j < pthreadPool.tidArr.workerNum; ++j){
                    pthread_join(pthreadPool.tidArr.Arr[j], NULL); /*等待子线程退出*/
                }
                printf("all worker thread exited, exiting main thread...\n");
                exit(0);
            }
        }
    }

    return 0;
}