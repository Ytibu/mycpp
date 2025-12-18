#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__ 

#include <arpa/inet.h>
#include <string>
using std::string;


// InetAddress类，实现获取ip和端口等信息

class InetAddress
{ 
public:
    InetAddress(const string &ip, unsigned short port); // 根据ip和端口构造InetAddress类对象
    InetAddress(const struct sockaddr_in &addr);    // 根据sockaddr_in构造InetAddress类对象
    ~InetAddress();
    string ip() const;  // 获取ip
    unsigned short port() const;    // 获取端口
    const struct sockaddr_in* getSockAddr() const;  // 获取sockaddr_in结构体
private:
    struct sockaddr_in _addr;
};

#endif