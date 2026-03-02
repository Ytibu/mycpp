#include "head.h"

// 创建子进程，父进程将子进程的pid和状态保存在workerArr数组中，子进程进入死循环，等待父进程的信号
int makeWorker(int workerNum, workerdata_t *workerArr)
{
    for (int i = 0; i < workerNum; ++i)
    {
        int pipefd[2];
        socketpair(AF_LOCAL, SOCK_STREAM, 0, pipefd);
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            // 子进程
            close(pipefd[0]);
            workerLoop(pipefd[1]);
        }
        else
        {
            // 父进程
            close(pipefd[1]);

            workerArr[i].pid = pid;
            workerArr[i].status = FREE;
            workerArr[i].pipesockfd = pipefd[0];
            printf("worker %d is ready, pid = %d, status = %d, pipefd = %d\n", i+1, pid, workerArr[i].status, pipefd[0]);
        }
    }

    return 0;
}

int workerLoop(int sockFd)
{
    while (1)
    {
        int netFd;
        int exitFlag;
        int ret = recvfd(sockFd, &netFd, &exitFlag);
        if (ret <= 0)
        {
            break;
        }
        if(exitFlag == 1){
            printf("worker %d is exiting\n", getpid());
            close(sockFd);
            exit(0);
        }
        
        printf("worker %d is working\n", getpid());
        
        transFile(netFd);
        close(netFd);

        pid_t pid = getpid();
        send(sockFd, &pid, sizeof(pid), 0);
    }

    return 0;
}