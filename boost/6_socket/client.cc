#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>


using std::cout;
using std::endl;
using std::string;


//利用c语言socket编程实现一个TCP客户端：创建socket → 连接服务器 → 通信


int main(int argc, char *argv[]){

    //创建套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0){
        perror("socket");
        return;
    }


    //初始化服务器的地址结构，方便连接服务器
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(atoi(argv[2]));


    //连接服务器
    int ret = connect(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if(ret < 0){
        perror("connect");
        close(listenfd);
        return;
    }


    //通信
    while(1){
        cout << "Please input message: " << endl;
        string line;
        getline(std::cin, line);
        int len2 = send(listenfd, line.c_str(), line.size(), 0);
        if(len2 < 0){
            cout << "send error" << endl;
        }else if(len2 == 0){
            cout << "server close" << endl;
        }else{
            cout << "send " << len2 << " bytes" << endl;
        }

        char buf[1024] = {0};
        int len = recv(listenfd, buf, sizeof(buf), 0);
        if(len < 0){
            cout << "recv error" << endl;
        }else if(len == 0){
            cout << "server close" << endl;
        }else{
            cout << "recv " << len << " bytes" << endl;
            cout << buf << endl;
        }
    }

    close(listenfd);
    return 0;

}