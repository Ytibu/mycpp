#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/**
 * 客户端基本流程：
 * 1. 创建套接字
 * 2. 连接服务器
 * 3. 与服务器通信
 * 4. 关闭套接字
 */
void client(const char *ip, int port)
{

    // 初始化服务器地址结构体
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        return;
    }

    // 建立连接：将套接字连接到服务器地址
    int conn_ret = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    if (conn_ret < 0)
    {
        perror("connect");
        return;
    }

    // 通信：发送和接收数据

    // 发送数据
    int sen_ret = send(sockfd, "this is client\n", 19, 0);
    if (sen_ret < 0)
    {
        perror("send");
        exit(1);
    }

    // 接收数据
    char buf[1024] = {0};
    int recv_ret = recv(sockfd, buf, sizeof(buf) - 1, 0);
    if (recv_ret <= 0)
    {
        if (recv_ret < 0)
        {
            perror("recv");
            exit(1);
        }
    }

    buf[recv_ret] = '\0';
    printf("client has received: %s\n", buf);

    sleep(1);

    close(sockfd);
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        fprintf(stderr, "argc error\n");
        exit(1);
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    client(ip, port);

    return 0;
}