#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

/**
 * int setsockopt (int __fd, int __level, int __optname, const void *__optval, socklen_t __optlen)
 * setsockopt函数用于设置套接字选项，参数说明如下：
 * __fd：套接字文件描述符。
 * __level：选项所在的协议层次，常用的有SOL_SOCKET（套接字层）和IPPROTO_TCP（TCP协议层）。
 * __optname：要设置的选项名称，常用的有SO_REUSEADDR（地址复用）和SO_KEEPALIVE（保持连接）。
 * __optval：指向包含选项值的缓冲区的指针。
 * __optlen：选项值的长度。
 * 返回值：成功时返回0，失败时返回-1，并设置errno以指示错误原因。
 * 该函数可以用于设置套接字的各种选项，例如启用地址复用以允许多个套接字绑定到同一地址和端口，或者启用保持连接以检测死连接。
 */

/**
 * select + socket 实现双端即时通信
 * 服务器端可以同时监听标准输入和客户端发送的数据，当标准输入有数据时，发送给客户端；当客户端发送数据时，打印出来
 */

void Server(const char *ip, int port)
{
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        perror("socket error");
        exit(1);
    }

    // 设置地址复用
    int reuse = 1;
    int ret = setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    if (ret < 0)
    {
        perror("setsockopt error");
        exit(1);
    }
    ret = bind(sockFd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0)
    {
        perror("bind error");
        exit(1);
    }

    ret = listen(sockFd, 50);
    if (ret < 0)
    {
        perror("listen error");
        exit(1);
    }

    int acceptFd = accept(sockFd, NULL, NULL);
    if (acceptFd < 0)
    {
        perror("accept error");
        exit(1);
    }

    fd_set rdset;
    char buf[1024] = {0};
    int maxFd = acceptFd > STDIN_FILENO ? acceptFd : STDIN_FILENO;
    while (1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(acceptFd, &rdset);
        ret = select(maxFd + 1, &rdset, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select error");
            exit(1);
        }

        if (FD_ISSET(STDIN_FILENO, &rdset))
        {
            memset(buf, 0, sizeof(buf));
            int read_len = read(STDIN_FILENO, buf, sizeof(buf));
            send(acceptFd, buf, read_len, 0);
        }
        if (FD_ISSET(acceptFd, &rdset))
        {
            memset(buf, 0, sizeof(buf));
            int recv_len = recv(acceptFd, buf, sizeof(buf), 0);
            if (recv_len < 0)
            {
                perror("recv error");
                break;
            }
            else if (recv_len == 0)
            {
                printf("client closed\n");
                break;
            }
            else
            {
                printf("recv from client: %s", buf);
            }
        }
    }
    close(acceptFd);
    close(sockFd);
}

// ./select_Server ip port
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("argc error\n");
        exit(1);
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    Server(ip, port);

    return 0;
}