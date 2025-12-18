#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__ 

#include <arpa/inet.h>
#include <string>
using std::string;


//InetAddress类：实现了sockaddr_in结构体的创建，获取ip与端口号，获取sockaddr_in结构体


class InetAddress
{ 
public:
    InetAddress(const string &ip, unsigned short port); //根据ip与port创建InetAddress
    InetAddress(const struct sockaddr_in &addr);    //根据sockaddr_in结构体创建InetAddress
    ~InetAddress();
    string ip() const;  //获取ip
    unsigned short port() const;    //获取端口号
    const struct sockaddr_in* getSockAddr() const;  //获取sockaddr_in结构体
private:
    struct sockaddr_in _addr;
};

#endif