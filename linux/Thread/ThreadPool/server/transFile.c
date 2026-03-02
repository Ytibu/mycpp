#include "transFile.h"

#include "errorSet.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>



int transFile(int netFd)
{
    // 文件名发送
    train_t train;
    char fileName[] = "download.txt";
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

    sendfile(netFd, fd, NULL, statbuf.st_size);

    close(fd);
    return 0;
}