#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__ 

#include "Socket.h"
#include "InetAddress.h"

#include <string>


using std::string;


// Acceptor类：实现地址与端口复用，bind绑定，listen监听，accept接受连接

class Acceptor : NonCopyable {
    
public:
    Acceptor(const string &ip, unsigned short port);    // 构造函数:接收 字符串ip 和 无符号短整形端口号
    ~Acceptor();
    void ready();   // 即：绑定，监听，设置地址端口复用

private:    //此函数供共有函数(ready())调用(简化函数调用代码)
    void setReuseAddr();    // 设置地址复用
    void setReusePort();    // 设置端口复用
    void bind();    // 地址绑定
    void listen();  // 设置监听

public:
    int accept();   // 阻塞等待连接
    int fd() const; // 获取文件描述符
    
private:
    Socket _sock;   // socket套接字初始化交给Socket类
    InetAddress _addr;  // 地址初始化交给InetAddress类
};

#endif