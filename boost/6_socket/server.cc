#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>  // 用于 sockaddr_in 结构体
#include <arpa/inet.h>  // 用于 inet_addr 和 htons 函数

#include <iostream>
#include <string>


using std::cout;
using std::endl;
using std::string;


//利用c语言socket编程实现一个简单的TCP服务器：创建一个socket，绑定一个ip和端口，监听，接收数据，发送数据，关闭socket


int main(int argc, char *argv[]){

    //创建socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0); // 使用ipv4协议，TCP协议，默认协议
    if(listenfd < 0){
        cout << "create socket error" << endl;
        return;
    }

    //设置端口复用与地址复用
    int opt = 1;
    int retavl = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // 设置地址复用
    if(retavl < 0){
        cout << "set socket error" << endl;
        return;
    }
    int opt2 = 1;
    int retavl2 = setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt2, sizeof(opt2));  // 设置端口复用
    if(retavl2 < 0){
        cout << "set socket error" << endl;
        return;
    }


    //初始化并创建 服务端地址结构体
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));   // 初始化服务端地址结构体为0
    server_addr.sin_family = AF_INET;   // 设置协议族为ipv4
    //字节序转换
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    

    //将sockaddr结构体(服务器地址与端口号)永久绑定给listenfd(监听套接字)
    int ret = bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0) {
        perror("bind");
        close(listenfd);
        return;
    }


    //开始监听
    ret = listen(listenfd, 5);
    if (ret < 0) {
        perror("listen");
        close(listenfd);
        return;
    }

    cout << "listenfd = " << listenfd << endl;

    #if 0
    //客户端ip、端口
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));   //初始化结构体
    client_addr.sin_family = AF_INET;               //协议族
    socklen_t client_addr_len = sizeof(client_addr);//结构体大小
    accept(listenfd, (struct sockaddr*)&client_addr, &client_addr_len);
    #endif

    //接收任何连接
    int connfd = accept(listenfd, nullptr, nullptr);
    if(connfd < 0){
        perror("accept");
        close(listenfd);
        return;
    }


    //数据通信
    while(true){ 
        char buf[1024] = {0};
        int len = recv(connfd, buf, sizeof(buf), 0);
        if(len < 0){
            cout << "recv error" << endl;
        }else if(len == 0){
            cout << "client closed..." << endl;
            break;
        }else{
            cout << "client# " << buf << endl;
        }

        cout << "server# ";
        string line;
        getline(std::cin, line);
        int len2 = send(connfd, line.c_str(), line.length(), 0);
        if(len2 < 0){
            cout << "send error" << endl;
        }else if(len2 == 0){
            cout << "server closed..." << endl;
            break;
        }else{
            cout << "server# " << line << endl;
        }
    }

    // 关闭文件描述符
    close(listenfd);
    close(connfd);


}