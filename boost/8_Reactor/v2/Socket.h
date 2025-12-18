#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "NonCopyable.h"


//Socket类：封装了socket，实现socket的创建，关闭等操作


class Socket : NonCopyable
{
public:
    Socket();   //创建socket
    Socket(int fd); //创建socket(直接使用传入的文件描述符)
    ~Socket();
    int fd() const; //返回socket的文件描述符
    void shutDownWrite();   //关闭socket(仍接收数据)
private:
    int _fd;
};

#endif