#ifndef __TRANSFILE_H__
#define __TRANSFILE_H__

typedef struct train_s
{
    int length;
    char data[1000];
} train_t;

int transFile(int netFd);

#endif