#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__ 

#include "Socket.h"
#include "InetAddress.h"

#include <string>


using std::string;


// Acceptor类：实现地址与端口复用，bind绑定，listen监听，accept接受连接

class Acceptor : NonCopyable {
public:
    Acceptor(const string &ip, unsigned short port);
    ~Acceptor();
    void ready();
private:
    void setReuseAddr();
    void setReusePort();
    void bind();
    void listen();
public:
    int accept();
    int fd() const;
private:
    Socket _sock;
    InetAddress _addr;
};

#endif