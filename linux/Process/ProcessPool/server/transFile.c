#include "head.h"

// 1.0 发送文件名和文件内容
// int transFile(int netfd){
//   char filename[] = "file1";
//   send(netfd,filename,5,0);
//   int fd = open(filename,O_RDWR);
//   char buf[1000] = {0};
//   ssize_t sret = read(fd,buf,sizeof(buf));
//   send(netfd,buf,sret,0);
//   return 0;
//}


// 粘包问题：发送端发送多个包，但是接收端可能一次读取多个包，导致包之间没有界限
// 2.1 解决粘包问题：通过定义包头+包体结构体，读取指定长度的包头，根据包头的内容读取包体
typedef struct train_s
{
    int length;
    char data[1000];
} train_t;
// int transFile(int netFd){
//     train_t train;

//     // 发送文件名
//     char filename[] = "file1";
//     train.length = strlen(filename);
//     memcpy(train.data,filename,train.length);
//     send(netFd,&train,sizeof(train.length)+train.length,0);

//     int fd = open(filename,O_RDWR);
//     ERROR_CHECK(fd, -1, "open");

//     // 发送文件内容
//     ssize_t sret = read(fd,train.data,sizeof(train.data));
//     train.length = sret;
//     send(netFd,&train,sizeof(train.length)+train.length,0);

//     close(fd);
//     return 0;
// }


// 半包问题：发送端发送一个包，但是接收端可能一次读取不到指定长度的数据，导致包不完整
// 2.2 解决半包问题：通过引入recv的MSG_WAITALL参数，保证接收指定长度的数据
//  引入recv的MSG_WAITALL参数，保证接收指定长度的数据
// int transFile(int netfd){
//    train_t train;
//    char filename[] = "file1";
//    // 组装小火车
//    train.length = strlen(filename);
//    memcpy(train.data,filename,train.length);
//    // 发送小火车 头长度+车厢长度
//    send(netfd,&train,sizeof(train.length)+train.length,MSG_NOSIGNAL);
//
//    int fd = open(filename,O_RDWR);
//    while(1){
//        ssize_t sret = read(fd,train.data,sizeof(train.data));
//        train.length = sret;
//        ssize_t sret1 = send(netfd,&train,sizeof(train.length)+train.length,MSG_NOSIGNAL);
//        if(sret == 0 || sret1 == -1){
//            break;
//        }
//        sleep(1);
//    }
//    close(fd);
//    return 0;
//}


// 3.0 发送文件大小，让接收端能够实时计算接受进度
// int transFile(int netFd)
// {
//     // 文件名发送
//     train_t train;
//     char fileName[] = "demo.txt";
//     train.length = strlen(fileName);
//     memcpy(train.data, fileName, train.length);
//     send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);

//     // 文件大小发送
//     struct stat statbuf;
//     int fd = open(fileName, O_RDWR);
//     ERROR_CHECK(fd, -1, "open");
//     fstat(fd, &statbuf);
//     train.length = sizeof(off_t);
//     memcpy(train.data, &statbuf.st_size, train.length);
//     send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);
//     while (1)
//     {
//         ssize_t sret = read(fd, train.data, sizeof(train.data));
//         train.length = sret;
//         ssize_t send_ret = send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);
//         if (sret == 0 || send_ret == -1)
//         {
//             break;
//         }
//     }
//     close(fd);
//     return 0;
// }


// 多次拷贝：文件内容从磁盘拷贝到内核空间(read)，再从内核空间拷贝到用户空间(recv)，最后从用户空间通过网络发送出去，效率较低
// 4.1 利用内存映射，将磁盘数据映射到内存，直接操作内存，减少一次拷贝，提高效率
// int transFile(int netFd)
// {
//     // 文件名发送
//     train_t train;
//     char fileName[] = "demo.txt";
//     train.length = strlen(fileName);
//     memcpy(train.data, fileName, train.length);
//     send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);

//     // 文件大小发送
//     struct stat statbuf;
//     int fd = open(fileName, O_RDWR);
//     ERROR_CHECK(fd, -1, "open");
//     fstat(fd, &statbuf);
//     train.length = sizeof(off_t);
//     memcpy(train.data, &statbuf.st_size, train.length);
//     send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);

//     char *pFD = (char *)mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//     ERROR_CHECK(pFD, MAP_FAILED, "mmap");

//     off_t cursize = 0;
//     while(1){
//         if(cursize >= statbuf.st_size){
//             break;
//         }
//         if(statbuf.st_size - cursize >= 1000){
//             train.length = 1000;
//         }else{
//             train.length = statbuf.st_size - cursize;
//         }
//         send(netFd, &train.length, sizeof(train.length), MSG_NOSIGNAL);
//         send(netFd, pFD + cursize, train.length, MSG_NOSIGNAL);
//         cursize += train.length;
//     }
//     train.length = 0;
//     send(netFd, &train.length, sizeof(train.length), MSG_NOSIGNAL);

//     munmap(pFD, statbuf.st_size);
//     close(fd);
//     return 0;
// }


// 4.2 发送端将所有内容作为一个大的整体包，接收端一次性接收大包，减少多次发送和接收的开销，提高效率
int transFile(int netFd)
{
    // 文件名发送
    train_t train;
    char fileName[] = "demo.txt";
    train.length = strlen(fileName);
    memcpy(train.data, fileName, train.length);
    send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);

    // 文件大小发送
    struct stat statbuf;
    int fd = open(fileName, O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    fstat(fd, &statbuf);
    train.length = sizeof(off_t);
    memcpy(train.data, &statbuf.st_size, train.length);
    send(netFd, &train, sizeof(train.length) + train.length, MSG_NOSIGNAL);

    // char *pFD = (char *)mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    // ERROR_CHECK(pFD, MAP_FAILED, "mmap");

    // send(netFd, pFD, statbuf.st_size, MSG_NOSIGNAL);

    // munmap(pFD, statbuf.st_size);

    sendfile(netFd, fd, NULL, statbuf.st_size);

    close(fd);
    return 0;
}