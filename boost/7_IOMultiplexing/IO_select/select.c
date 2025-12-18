#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <ctype.h>

#define SERVER_PORT 8888


//IO多路复用下，利用select来完成IO多路复用的TCP服务器
int main(int argc, char *argv[])
{
    int listenfd, connfd, sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len; 
    int ret, maxfd, maxi, i, j, nready, nByte;
    fd_set rset, allset;

    int client[FD_SETSIZE];
    char buf[BUFSIZ], str[BUFSIZ];

    // 创建套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        perror("socket error");
        return;
    }


    //地址与端口复用
    int pot = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &pot, sizeof(pot));
    #if 0
    int opt2 = 1;
    setsockopt(listenfd,SOL_SOCKET,SO_REUSEPORT,&opt2,sizeof(opt2));
    #endif

    //设置服务器地址结构体
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //绑定地址与端口
    ret = bind(listenfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0)
    {
        perror("bind");
        close(listenfd);
        return;
    }


    //开始监听
    ret = listen(listenfd, 128);
    if(ret == -1){
        perror("listen");
        close(listenfd);
        return;
    }

    printf("listenfd = %d\n", listenfd);

    //select类型为IO多路复用
    maxfd = listenfd;
    maxi = -1;
    //待监听的存放文件描述符数组的初始化
    for(int i = 0; i < FD_SETSIZE; i++){
        client[i] = -1;
    }

    FD_ZERO(&allset);   //清空allset
    FD_SET(listenfd, &allset);  //监听套接字

    while(1){
        rset = allset;

        //select调用
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(nready < 0){
            perror("select error");
            close(listenfd);
            return;            
        }

        //监听到listenfd，表示有新的请求建立连接·
        if(FD_ISSET(listenfd, &rset)){

            client_addr_len = sizeof(client_addr);

            //阻塞等待客户端发起连接
            connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_addr_len);
            if(connfd < 0){
                perror("accept error");
                return;
            }

            printf("client ip: %s, port: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            // 将新的连接描述符加入到数组中
            for(i = 0; i < FD_SETSIZE; ++i){
                if(client[i] < 0){
                    client[i] = connfd;
                    printf("add new client fd %d, position %d\n", connfd, i);
                    break;
                } 
            }

            //超过最大连接数
            if(i == FD_SETSIZE){
                fputs("too many clients\n", stderr);
                return;
            }

            //将三次握手的文件描述符放入allset集合中
            FD_SET(connfd, &allset);

            //更新maxfd
            if(connfd > maxfd)
                maxfd = connfd;
            //更新maxi
            if(i > maxi)
                maxi = i;
            //继续循环监听到可读事件
            if(--nready == 0)
                continue; 

        }

        //遍历client数组，查看文件描述符是否为被监听，否则继续循环
        for(i = 0; i <= maxi; i++)
        {
            if((sockfd = client[i]) < 0)
                continue; 
            
            //判断文件描述符是否可读
            if(FD_ISSET(sockfd, &rset)){

                if((nByte = read(sockfd, buf, sizeof(buf))) == 0){
                    close(sockfd);
                    printf("client[%d] closed connection\n", i);
                    FD_CLR(sockfd, &rset);
                    client[i] = -1;
                }
                else if(nByte > 0) {
                    for(j = i + 1; j <= nByte; j++)
                        buf[j] = toupper(buf[j]);
                    write(sockfd, buf, nByte);
                    write(STDOUT_FILENO, buf, nByte);
                }
                if(--nready == 0)
                    break;
            }
        }
    }

}