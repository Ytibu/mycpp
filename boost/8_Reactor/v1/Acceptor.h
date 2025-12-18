#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__ 

#include "Socket.h"
#include "InetAddress.h"
#include <string>
using std::string;



//Acceptor类，实现了socket的地址和端口监听，地址与端口绑定，监听，接受连接，返回socket文件描述符


class Acceptor : NonCopyable {
public:
    Acceptor(const string &ip, unsigned short port);    //接收ip和端口，创建socket，创建Acceptor对象
    ~Acceptor();
    void ready();   //简化对外接口的代码量(调用封装私有化的函数：setReuseAddr, setReusePort, bind, listen)
private:
    void setReuseAddr();    //设置地址复用
    void setReusePort();    //设置端口复用
    void bind();    //绑定
    void listen();  //监听
public:
    int accept();   //接受连接
    int fd() const; //获取文件描述符
private:
    Socket _sock;
    InetAddress _addr;
};

#endif