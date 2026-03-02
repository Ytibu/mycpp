#include "head.h"

int exitPipe[2];
void handler(int signum)
{
    printf("signum = %d\n", signum);
    write(exitPipe[1], "1", 1);
}

// server.out 0.0.0.0 1234 5
int main(int argc, char *argv[])
{
    // 参数检验
    ARGS_CHECK(argc, 4, "argc error");

    // 创建进程池信息数组，创建子进程池
    int workerNum = atoi(argv[3]);
    workerdata_t *workerArr = (workerdata_t *)calloc(workerNum, sizeof(workerdata_t));
    ERROR_CHECK(workerArr, NULL, "calloc");
    makeWorker(workerNum, workerArr);

    // 创建退出管道，注册信号处理函数
    pipe(exitPipe);
    signal(SIGUSR1, handler);

    // 初始化tcp
    int sockfd;
    tcpInit(argv[1], atoi(argv[2]), &sockfd);

    // 将监听套接字添加到epoll中
    int epfd = epoll_create(1);
    epollAdd(epfd, sockfd);

    // 遍历各个子进程，并监听各个子进程的pipesockFd
    for (int i = 0; i < workerNum; ++i)
    {
        epollAdd(epfd, workerArr[i].pipesockfd);
    }
    epollAdd(epfd, exitPipe[0]);

    // 事件循环
    while (1)
    {
        struct epoll_event readySet[1024];
        int readyNum = epoll_wait(epfd, readySet, 1024, -1);
        for (int i = 0; i < readyNum; ++i)
        {
            // 监听套接字就绪，说明有新的客户端连接
            if (readySet[i].data.fd == sockfd)
            {
                int netfd = accept(sockfd, NULL, NULL);
                printf("new client is connecting, netfd = %d\n", netfd);
                // TODO:分发任务
                for (int j = 0; j < workerNum; ++j)
                {
                    if (workerArr[j].status == FREE)
                    {
                        sendfd(workerArr[j].pipesockfd, netfd, 0); /* 通知空闲进程池，新的客户端连接*/
                        workerArr[j].status = BUSY;
                        break;
                    }
                }
                close(netfd); // 主进程关闭客户端连接，由子进程处理客户端连接
            }
            else if (readySet[i].data.fd == exitPipe[0])
            {
                // 收到退出信号，通知所有子进程退出，并回收资源
                printf("exit signal is coming\n");
                char flag;
                read(exitPipe[0], &flag, 1);
                for (int j = 0; j < workerNum; ++j)
                {
                    sendfd(workerArr[j].pipesockfd, 0, 1); /* 通知所有子进程退出*/
                }
                for(int j = 0; j < workerNum; ++j)
                {
                    wait(NULL);
                }

                printf("kill workerPool successfully\n");

                free(workerArr);
                close(epfd);
                close(sockfd);
                close(exitPipe[0]);
                close(exitPipe[1]);
                exit(0);
            }
            else
            {
                int pipesockFd = readySet[i].data.fd;
                for (int j = 0; j < workerNum; ++j)
                {
                    if (workerArr[j].pipesockfd == pipesockFd)
                    {
                        pid_t pid;
                        recv(pipesockFd, &pid, sizeof(pid), 0);
                        printf("worker %d is free\n", pid);
                        workerArr[j].status = FREE;
                        break;
                    }
                }
            }
        }
    }

    return 0;
}