#include <poll.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>

#define SERV_PORT 8888
#define OPEN_MAX 1024


//IO多路复用下，利用poll来完成多路复用的服务器


int main(){


    int i, j, n, maxi;
    int nready, ret;
    int listenfd, connfd, sockfd;
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];
    struct sockaddr_in cli_addr, serv_addr;
    socklen_t cli_addr_len;
    struct pollfd client[OPEN_MAX];


    //创建套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0){
        perror("socket error");
        return;
    }


    //地址复用
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));


    //地址结构体定义与初始化
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    //绑定地址结构体
    ret = bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(ret == -1){
        perror("bind error");
        close(listenfd);
        return;
    }

    //服务器监听
    ret = listen(listenfd, 128);
    if(ret == -1){
        perror("listen error");
        close(listenfd);
        return;
    }


    //创建epoll设置监听
    client[0].fd = listenfd;
    client[0].events = POLLIN;

    for (size_t i = 0; i < OPEN_MAX; i++)
        client[i].fd = -1;  //初始化
    
    maxi = 0;
    
    //数据接收
    while(1){

        nready = poll(client, maxi + 1, -1);    //监听client,监听数+1，-1表示阻塞
        if(nready < 0){
            perror("poll");
            close(listenfd);
            return;
        }

        //有监听事件，且监听事件为读事件
        if(client[0].revents & POLLIN){ 
            cli_addr_len = sizeof(cli_addr);
            connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cli_addr_len);
            if(connfd < 0){
                perror("accept");
                return;
            }

            printf("client ip: %s, port: %d\n", inet_ntoa(cli_addr.sin_addr), cli_addr.sin_port);

            //将新连接的套接字加入client数组中，存储建立连接的描述符
            for(int i = 0; i < OPEN_MAX; i++){
                if(client[i].fd < 0){   //判断是否初始化，且作处理
                    client[i].fd = connfd;
                    break;
                }
            }

            if(i == OPEN_MAX){      //如果client数组已满即超过最大连接
                fputs("too many clients\n", stderr);
                return;
            }

            client[i].events = POLLIN;

            if(i > maxi)
                maxi = i;
            
            if(--nready == 0)
                continue;
        }
    }

}