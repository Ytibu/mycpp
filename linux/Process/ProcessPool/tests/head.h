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
#include <sys/wait.h>

// 参数检验
#define ARGS_CHECK(argc, num, str) \
    do { \
        if ((argc) != (num)) { \
            printf("%s\n", (str)); \
            exit(1); \
        } \
    } while (0)

// 错误检验
#define ERROR_CHECK(ret, val, str) \
    do { \
        if ((ret) == (val)) { \
            perror((str)); \
            exit(1); \
        } \
    } while (0)

// #define FREE 0
// #define BUSY 1
enum {
    FREE,
    BUSY
};

//主进程使用，保存各个子进程的信息
typedef struct workerdata_s{
    pid_t pid; //子进程的pid
    int status;
} workerdata_t;


//子进程创建函数
int makeWorker(int workerNum, workerdata_t *workerArr);

//tcp初始化函数
int tcpInit(const char *ip, const int port, int *pSockfd);

//epoll相关函数
int epollAdd(int epfd, int fd);
int epollDel(int epfd, int fd);