#include "SocketIO.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>


SocketIO::SocketIO(int fd)
    : _fd(fd)
{
}

SocketIO ::~SocketIO()
{
    close(_fd);
}


int SocketIO::readn(char *buf, int len)
{
    int left = len;
    char *p = buf;
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