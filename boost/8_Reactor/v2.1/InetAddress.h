#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__ 

#include <arpa/inet.h>
#include <string>


using std::string;


//InetAddress类：实现了sockaddr_in结构体的创建，获取ip与端口号，获取sockaddr_in结构体


class InetAddress
{ 
public:
    InetAddress(const string &ip, unsigned short port);
    InetAddress(const struct sockaddr_in &addr);
    ~InetAddress();
    string ip() const;
    unsigned short port() const;
    const struct sockaddr_in* getSockAddr() const;
private:
    struct sockaddr_in _addr;
};

#endif