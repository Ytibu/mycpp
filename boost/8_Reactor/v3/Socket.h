#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "NonCopyable.h"


//Socket类：封装了socket，实现socket的创建，关闭等操作


class Socket : NonCopyable
{
public:
    Socket();   //创建socket，生成socket文件描述符
    Socket(int fd); // 创建socket，传入socket文件描述符
    ~Socket();  // 关闭socket
    int fd() const; // 返回socket文件描述符
    void shutDownWrite();   // 关闭socket的写端
private:
    int _fd;
};

#endif