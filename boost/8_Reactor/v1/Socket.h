#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "NonCopyable.h"

class Socket : NonCopyable
{
public:
    Socket();
    Socket(int fd);
    ~Socket();
    int fd() const;
    // int getFd() const;
    // void bind(const InetAddress &addr);
    // void listen();
    // int accept();
    // void shutdownWrite();
    // void close();
    // void setReuseAddr(bool on);
    // void setReusePort(bool on);
    // void setKeepAlive(bool on);
    void shutDownWrite();
private:
    int _fd;
};

#endif