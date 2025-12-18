#include <iostream>
using std::cout;
#include <Cfun.h>

/*字节序转换*/
void test(){

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(8888);
    char ip[] = "127.0.0.1";
    inet_aton(ip,&sockaddr.sin_addr);
    printf("ip = %x\n",sockaddr.sin_addr.s_addr);
    printf("port = %x\n",sockaddr.sin_port);

}

int main(){

    

}