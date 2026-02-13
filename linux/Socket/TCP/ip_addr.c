#include <sys/socket.h>
#include <arpa/inet.h>


/**
 * IP地址在socket编程中是通过sockaddr_in结构体来表示的，sockaddr_in结构体包含了IP地址和端口号等信息。
 * 
 * #include <sys/socket.h>
 * struct sockaddr{
 *      sa_family_t sa_family; //地址族
 *      char sa_data[14]; //地址数据
 * };
 * 
 * struct sockaddr_in{
 *      sa_family_t sin_family; //地址族
 *      uint16_t sin_port; //端口号
 *      struct in_addr sin_addr; //IP地址
 * };
 * struct in_addr{
 *      uint32_t s_addr; //IP地址
 * };
 * 
 * 
 * 端口号的转换函数：
 *      #include <arpa/inet.h>
 *      uint32_t htonl(uint32_t hostlong);  //将主机字节序转换为网络字节序
 *      uint16_t htons(uint16_t hostshort); //将主机字节序转换为网络字节序
 *      uint32_t ntohl(uint32_t netlong);   //将网络字节序转换为主机字节序
 *      uint16_t ntohs(uint16_t netshort);  //将网络字节序转换为主机字节序
 * 
 * 
 * IP地址的转换函数：
 *      #include <arpa/inet.h>
 *      int inet_aton(const char *cp, struct in_addr *inp);   //将点分十进制的IP地址转换为网络字节序的二进制形式
 *      in_addr_t inet_addr(const char *cp);                 //将点分十进制的IP地址转换为网络字节序的二进制形式，返回值是一个32位无符号整数
 *      in_addr_t inet_network(const char *cp);             //将点分十进制的IP地址转换为网络字节序的二进制形式，返回值是一个32位无符号整数
 *      char *inet_ntoa(struct in_addr in);                //将网络字节序的二进制形式的IP地址转换为点分十进制的字符串形式
 */

int main()
{
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8888);
    server_addr.sin_addr.s_addr =  inet_addr("127.0.0.1");
    //inet_aton("127.0.0.1", &server_addr.sin_addr);

    return 0;
}