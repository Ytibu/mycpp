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

// 1.0 发送文件名和文件内容
// int recvFile(int sockfd){
//    char filename[4096] = {0};
//    recv(sockfd,filename,sizeof(filename),0);
//    int fd = open(filename,O_CREAT|O_RDWR,0666);
//    char buf[1000] = {0};
//    ssize_t sret = recv(sockfd,buf,sizeof(buf),0);
//    write(fd,buf,sret);
//    return 0;
//}


// 2.1 解决粘包问题：采用小火车：火车头显示数据长度，火车厢存储数据内容
typedef struct train_s
{
    int length;
    char data[1000];
} train_t;
// int recvFile(int sockfd){
//     char filename[4096] = {0};
//     train_t train;
//     // 先收火车头，以知道车厢实际长度
//     recv(sockfd,&train.length,sizeof(train.length),0);
//     recv(sockfd,train.data,train.length,0);
//     memcpy(filename,train.data,train.length);
//
//     int fd = open(filename,O_CREAT|O_RDWR,0666);
//     recv(sockfd,&train.length,sizeof(train.length),0);
//     recv(sockfd,train.data,train.length,0);
//     write(fd,train.data,train.length);
//     close(fd);
//     return 0;
// }


// 2.2 解决半包问题：引入recv的MSG_WAITALL参数，保证接收指定长度的数据
// int recvFile(int sockfd){
//     char filename[4096] = {0};
//     train_t train;
//     // 先收火车头，以知道车厢实际长度
//     recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
//     recv(sockfd,train.data,train.length,MSG_WAITALL);
//     memcpy(filename,train.data,train.length);
//
//     int fd = open(filename,O_CREAT|O_RDWR|O_TRUNC,0666);
//     while(1){
//         recv(sockfd,&train.length,sizeof(train.length),MSG_WAITALL);
//         if(train.length != 1000){
//             printf("train.length = %d\n", train.length);
//         }
//         if(train.length == 0){
//             break;
//         }
//         recv(sockfd,train.data,train.length,MSG_WAITALL);
//         write(fd,train.data,train.length);
//     }
//     close(fd);
//     return 0;
// }


// 3.1 解决半包问题2.0：通过包装recv函数，手动编码让recv函数保证接收指定长度的数据，增强兼容性(MSG_WITALL)
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
// int recvFile(int sockFd)
// {
//     char filename[4096] = {0};
//     train_t train;
//     // 先收火车头，以知道车厢实际长度
//     recvn(sockFd, &train.length, sizeof(train.length));
//     recvn(sockFd, train.data, train.length);
//     memcpy(filename, train.data, train.length);

//     int fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0666);
//     while (1)
//     {
//         recvn(sockfd, &train.length, sizeof(train.length));
//         if (train.length != 1000)
//         {
//             printf("train.length = %d\n", train.length);
//         }
//         if (train.length == 0)
//         {
//             break;
//         }
//         recvn(sockFd, train.data, train.length);
//         write(fd, train.data, train.length);
//     }
//     close(fd);
//     return 0;
// }


// 4.0 根据文件大小以及当前接收的大小，实现进度显示
// int recvFile(int sockFd)
// {
//     // 文件名发送
//     char fileName[1024] = {0};
//     train_t train;
//     recvn(sockFd, &train.length, sizeof(train.length));
//     recvn(sockFd, train.data, train.length);
//     memcpy(fileName, train.data, train.length);

//     // 文件长度接收
//     off_t filesize;
//     recvn(sockFd, &train.length, sizeof(train.length));
//     recvn(sockFd, &train.data, train.length);
//     memcpy(&filesize, train.data, train.length);
//     printf("filesize = %ld\n", filesize);

//     int fd = open(fileName, O_RDWR | O_CREAT | O_TRUNC, 0666);
//     ERROR_CHECK(fd, -1, "open");

//     off_t cursize = 0;
//     off_t lastsize = 0;
//     off_t slice = filesize / 10000;
//     while (1)
//     {
//         ssize_t sret = recv(sockFd, &train.length, sizeof(train.length), MSG_WAITALL);
//         if (train.length != 1000)
//         {
//             printf("train.length = %d\n", train.length);
//         }

//         if (train.length == 0)
//         {
//             break;
//         }
//         cursize += train.length;
//         sret = recvn(sockFd, &train.data, train.length);
//         write(fd, train.data, train.length);
//         if (cursize - lastsize > slice)
//         {
//             int percent = (int)(cursize * 100.0 / filesize + 0.5);
//             printf("%3d%%\r", percent);
//             fflush(stdout);
//             lastsize = cursize;
//         }
//     }
//     printf("100%%\n");

//     close(fd);

//     return 0;
// }

// 5.0 利用内存映射，将磁盘数据映射到内存，直接操作内存，减少一次拷贝，提高效率
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

    return 0;
}