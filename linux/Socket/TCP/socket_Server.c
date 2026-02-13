#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/**
 * socket()函数用于创建一个套接字，返回一个文件描述符。
 *      int socket (int __domain, int __type, int __protocol)
 * bind()函数用于将套接字绑定到一个特定的地址和端口号。
 *      int bind (int __fd, const struct sockaddr *__addr, socklen_t __len)
 * listen()函数用于监听套接字，等待客户端连接。
 *      int listen (int __fd, int __n)
 * connect()函数用于连接到服务器。
 *      int connect (int __fd, const struct sockaddr *__addr, socklen_t __len)
 * accept()函数用于接受客户端连接，返回一个新的文件描述符，用于与客户端通信。
 *      int accept (int __fd, struct sockaddr *__addr, socklen_t *__addr_len)
 * send()函数用于向客户端发送数据。
 *      ssize_t send (int __fd, const void *__buf, size_t __n, int __flags)
 * recv()函数用于从客户端接收数据。
 *      ssize_t recv (int __fd, void *__buf, size_t __n, int __flags)
 * close()函数用于关闭套接字。
 *      int close (int __fd)
 */

/**
 * 服务器端的基本流程：
 * 1. 创建套接字
 * 2. 绑定地址和端口号
 * 3. 监听客户端连接
 * 4. 接受客户端连接
 * 5. 与客户端通信
 * 6. 关闭套接字
 */


/* socket实现双端通信 */
void server(const char *ip, int port)
{
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    // 创建套接字并绑定地址
    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        perror("socket");
        exit(1);
    }
    int ret = bind(sockFd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        perror("bind");
        exit(1);
    }

    // 监听并接受客户端连接
    sleep(1);

    ret = listen(sockFd, 5);
    if (ret < 0)
    {
        perror("listen");
        exit(1);
    }

    /* 接收客户端连接，并对客户端ipPort存储*/
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientFd = accept(sockFd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientFd < 0)
    {
        perror("accept");
        exit(1);
    }

    char buf[1024] = {0};
    int recv_ret = recv(clientFd, buf, sizeof(buf) - 1, 0);
    if (recv_ret <= 0)
    {
        if (recv_ret < 0)
        {
            perror("recv");
            exit(1);
        }
    }
    buf[recv_ret] = '\0';
    printf("server has received: %s", buf);
    printf("client ip: %s port: %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

    ret = send(clientFd, "hello, this is server", 21, 0);
    if (ret < 0)
    {
        perror("send");
        exit(1);
    }

    close(clientFd);

    close(sockFd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    server(ip, port);

    return 0;
}