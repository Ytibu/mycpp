#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/sendfile.h>
#include <signal.h>
#include <sys/wait.h>

// 参数检验
#define ARGS_CHECK(argc, num, str) \
    do                             \
    {                              \
        if ((argc) != (num))       \
        {                          \
            printf("%s\n", (str)); \
            exit(1);               \
        }                          \
    } while (0)

// 错误检验
#define ERROR_CHECK(ret, val, str) \
    do                             \
    {                              \
        if ((ret) == (val))        \
        {                          \
            perror((str));         \
            exit(1);               \
        }                          \
    } while (0)

// #define FREE 0
// #define BUSY 1
enum
{
    FREE,
    BUSY
};

// 主进程使用，保存各个子进程的信息
typedef struct workerdata_s
{
    pid_t pid; // 子进程的pid
    int status;
    int pipesockfd; // 主进程和子进程通信的管道
} workerdata_t;

// 子进程创建函数
int makeWorker(int workerNum, workerdata_t *workerArr);
int workerLoop(int sockFd);

// tcp初始化函数
int tcpInit(const char *ip, const int port, int *pSockfd);

// epoll相关函数
int epollAdd(int epfd, int fd);
int epollDel(int epfd, int fd);

// 文件描述符传递函数
int sendfd(int sockfd, int fdtosend, int exitFlag);
int recvfd(int sockfd, int *pfdtorecv, int *exitFlag);

// 文件传输函数
int transFile(int sockFd);
int recvn(int sockFd, void *buf, long total);