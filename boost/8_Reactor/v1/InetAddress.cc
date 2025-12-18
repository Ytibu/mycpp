#include "InetAddress.h"
#include <strings.h>


// 根据传参创建InetAddress对象
InetAddress::InetAddress(const string& ip, unsigned short port)
{
    ::bzero(&_addr, sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

// 根据传参(sockaddr_in结构体)创建InetAddress对象
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

// 获取端口号
unsigned short InetAddress::port() const
{
    return ntohs(_addr.sin_port);
}

// 获取sockaddr_in结构体
const struct sockaddr_in* InetAddress::getSockAddr() const
{
    return &_addr;
}