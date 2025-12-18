#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "NonCopyable.h"


//Socket类：封装了socket，实现socket的创建，关闭等操作


class Socket : NonCopyable
{
public:
    Socket();
    Socket(int fd);
    ~Socket();
    int fd() const;
    void shutDownWrite();
private:
    int _fd;
};

#endif