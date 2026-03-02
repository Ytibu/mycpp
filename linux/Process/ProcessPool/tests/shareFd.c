#include "head.h"

/*
 *   进程间传递文件描述符
 * ssize_t sendmsg (int __fd, const struct msghdr *__message,	int __flags);
 * ssize_t recvmsg (int __fd, struct msghdr *__message,         int __flags);
 * struct msghdr
    {
        void *msg_name;		// Address to send to/receive from.
        socklen_t msg_namelen;	// Length of address data.

        struct iovec *msg_iov;	// Vector of data to send/receive into.
        size_t msg_iovlen;		// Number of elements in the vector.

        void *msg_control;		// Ancillary data (eg BSD filedesc passing).
        size_t msg_controllen;	// Ancillary data buffer length.

        int msg_flags;		// Flags on received message.
    };

    struct iovec
    {
        void *iov_base;	// Pointer to data.
        size_t iov_len;	// Length of data.
    };

    struct cmsghdr
    {
        size_t cmsg_len;		// Length of data in cmsg_data plus length
        int cmsg_level;		// Originating protocol.
        int cmsg_type;		// Protocol specific type.
        unsigned char __cmsg_data[]; // Ancillary data.
    };
*/

int sendfd(int sockfd, int fdtosend)
{
    // 正文部分定义
    struct iovec msg_iov[1];
    char buf[] = "hello";
    msg_iov[0].iov_base = buf;
    msg_iov[0].iov_len = sizeof(buf);

    // 控制部分定义
    struct cmsghdr *msg_control = (struct cmsghdr *)malloc(CMSG_LEN(sizeof(int)));
    msg_control->cmsg_len = CMSG_LEN(sizeof(int));
    msg_control->cmsg_level = SOL_SOCKET;
    msg_control->cmsg_type = SCM_RIGHTS;
    memcpy(CMSG_DATA(msg_control), &fdtosend, sizeof(int));

    // msghdr定义
    struct msghdr hdr;
    bzero(&hdr, sizeof(hdr));
    hdr.msg_name = NULL;
    hdr.msg_namelen = 0;
    hdr.msg_iov = msg_iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = msg_control;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    hdr.msg_flags = 0;

    // 数据发送
    int ret = sendmsg(sockfd, &hdr, 0);
    ERROR_CHECK(ret, -1, "sendmsg");

    free(msg_control);
    return ret;
}

int recvfd(int sockfd, int *pfdtorecv)
{
    // 正文部分定义
    char buf[100] = {0};
    struct iovec msg_iov[1];
    msg_iov[0].iov_base = buf;
    msg_iov[0].iov_len = sizeof(buf);

    // 控制部分定义
    struct cmsghdr *msg_control = (struct cmsghdr *)malloc(CMSG_LEN(sizeof(int)));
    msg_control->cmsg_len = CMSG_LEN(sizeof(int));
    msg_control->cmsg_level = SOL_SOCKET;
    msg_control->cmsg_type = SCM_RIGHTS;

    // msghdr定义
    struct msghdr hdr;
    bzero(&hdr, sizeof(hdr));
    hdr.msg_name = NULL;
    hdr.msg_namelen = 0;
    hdr.msg_iov = msg_iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = msg_control;
    hdr.msg_controllen = CMSG_LEN(sizeof(int));
    hdr.msg_flags = 0;

    int ret = recvmsg(sockfd, &hdr, 0);
    ERROR_CHECK(ret, -1, "recvmsg");
    printf("recv buf = %s, fd = %d\n", buf, *(int *)CMSG_DATA(msg_control));
    *pfdtorecv = *(int *)CMSG_DATA(msg_control);

    free(msg_control);
    return ret;
}

int main(int argc, char *argv[])
{
    int fds[2];
    // pipe(fds);
    socketpair(AF_LOCAL, SOCK_STREAM, 0, fds); // 创建一个双向通信的管道

    if (fork())
    {
        close(fds[0]);
        int fdfile = open("demo.txt", O_RDWR | O_CREAT, 0664);
        printf("main fdfile = %d\n", fdfile);
        write(fdfile, "hello", 5);
        sendfd(fds[1], fdfile);

        wait(NULL);
    }
    else
    {
        close(fds[1]);
        int fdfile;
        recvfd(fds[0], &fdfile);
        printf("chiled  fdfile = %d\n", fdfile);
        int ret = write(fdfile, "world", 5);
        printf("ret = %d\n", ret);
    }

    return 0;
}