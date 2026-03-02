#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

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

typedef struct train_s
{
    int length;
    char data[1000];
} train_t;



int recvn(int sockFd, void *buf, long total)
{
    char *p = (char *)buf;
    long cursize = 0;
    while (cursize < total)
    {
        ssize_t sret = recv(sockFd, p + cursize, total - cursize, 0);
        if (sret == 0)
        {
            return 1;
        }
        cursize += sret;
    }
    return 0;
}

int recvFile(int sockFd)
{
    // 文件名发送
    char fileName[1024] = {0};
    train_t train;
    recvn(sockFd, &train.length, sizeof(train.length));
    recvn(sockFd, train.data, train.length);
    memcpy(fileName, train.data, train.length);

    // 文件长度接收
    off_t filesize;
    recvn(sockFd, &train.length, sizeof(train.length));
    recvn(sockFd, &train.data, train.length);
    memcpy(&filesize, train.data, train.length);
    printf("filesize = %ld\n", filesize);

    int fd = open(fileName, O_RDWR | O_CREAT | O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "open");

    ftruncate(fd, filesize);
    char *pFd = (char *)mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(pFd, MAP_FAILED, "mmap");

    recvn(sockFd, pFd, filesize);

    close(fd);

    return 0;
}

int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("argc error\n");
    }
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(atoi(argv[2]));
    serAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(sockFd, (struct sockaddr *)&serAddr, sizeof(serAddr));
    ERROR_CHECK(ret, -1, "connect");
    recvFile(sockFd);

    close(sockFd);
    return 0;
}