#include "SocketIO.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>


// 构造函数(读取传入的文件描述符的数据即socket套接字文件描述符)
SocketIO::SocketIO(int fd)
    : _fd(fd)
{
}

// 关闭文件描述符
SocketIO ::~SocketIO()
{
    close(_fd);
}

// 利用系统调用read函数，一次读取所有数据
int SocketIO::readn(char *buf, int len)
{

    char *p = buf;

    int left = len;
    while (left > 0)
    {
        int ret = ::read(_fd, p, left);
        if(ret == -1 && errno == EINTR)
            continue;
        else if (ret == -1)
        {
            perror("SocketIO::readn");
            return -1;
        }
        else if(ret == 0)
            break;
        else{
            p += ret;
            left -= ret;
        }
    }

    return len - left;
}

// 按行读取数据
int SocketIO::readLine(char *buf, int len)
{
    int left = len - 1;
    char *p = buf;
    int ret = 0, total = 0;

    while (left > 0)
    {
        ret = recv(_fd, p, left, MSG_PEEK);
        if(ret == -1 && errno == EINTR)
            continue;
        else if(ret == -1){
            perror("SocketIO::readLine");
            return -1; 
        }else if(ret == 0){
            break;
        }else
        {
            for (int idx = 0; idx < ret; ++idx){
                if (p[idx] == '\n'){
                    int sz = idx + 1;
                    readn(p, sz);
                    p[idx] = '\0';
                    return sz + total;
                }
            }

            readn(p, ret);
            total += ret;
            p += ret;
            left -= ret;
             
        }    
    }
    //*p = '\0';

    return total - left;
}


// 写入数据
int SocketIO::writen(const char *buf, int len)
{
    int left = len;
    const char *ptr = buf;
    int ret = 0;

    while (left > 0)
    {
        int ret = ::write(_fd, buf, left);
        if (ret == -1 && errno == EINTR)
            continue;
        else if (ret == -1){
            perror("write error");
            return -1;
        }else if(ret == 0){
            break;
        }else{
            ptr += ret;
            left -= ret;
        }

    }
    return len - left; 
}