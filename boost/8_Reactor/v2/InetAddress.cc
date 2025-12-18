#include "InetAddress.h"
#include <strings.h>


// 初始化InetAddress(利用ip,port参数，初始化Acceptor的socket地址)
InetAddress::InetAddress(const string& ip, unsigned short port)
{
    ::bzero(&_addr, sizeof(struct sockaddr_in));    // 初始化结构体
    _addr.sin_family = AF_INET; // ipv4
    _addr.sin_port = htons(port);   // 端口
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());  // ip
}

// 初始化InetAddress(利用sockaddr_in结构体初始化地址)
InetAddress::InetAddress(const struct sockaddr_in& addr):_addr(addr)
{
}

InetAddress::~InetAddress()
{
}

// 获取ip
string InetAddress::ip() const
{
    return string(inet_ntoa(_addr.sin_addr));
}

// 获取端口
unsigned short InetAddress::port() const
{
    return ntohs(_addr.sin_port);
}

// 获取sockaddr_in结构体
const struct sockaddr_in* InetAddress::getSockAddr() const
{
    return &_addr;
}