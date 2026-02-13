#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

void Client(const char *ip, int port)
{
    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = inet_addr(ip);

    int sockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFd < 0)
    {
        perror("socket error");
        exit(1);
    }

    int ret = connect(sockFd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    if (ret < 0)
    {
        perror("connect error");
        exit(1);
    }

    char buf[1024] = {0};
    fd_set rdset;
    while (1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sockFd, &rdset);

        ret = select(sockFd + 1, &rdset, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select error");
            exit(1);
        }

        if (FD_ISSET(STDIN_FILENO, &rdset))
        {
            memset(buf, 0, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf));
            send(sockFd, buf, strlen(buf), 0);
        }

        if (FD_ISSET(sockFd, &rdset))
        {
            memset(buf, 0, sizeof(buf));
            int recv_len = recv(sockFd, buf, sizeof(buf), 0);
            if (recv_len < 0)
            {
                perror("recv error");
                break;
            }
            else if (recv_len == 0)
            {
                printf("server closed\n");
                break;
            }
            else
            {
                printf("recv from server: %s", buf);
            }
        }
    }

    close(sockFd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("argc error\n");
        exit(1);
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    Client(ip, port);

    return 0;
}