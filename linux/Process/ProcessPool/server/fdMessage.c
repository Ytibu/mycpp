#include "head.h"

int sendfd(int sockfd, int fdtosend, int exitFlag)
{
    // 正文部分定义
    struct iovec msg_iov[1];
    msg_iov[0].iov_base = &exitFlag;
    msg_iov[0].iov_len = sizeof(int);

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

int recvfd(int sockfd, int *pfdtorecv, int *exitFlag)
{
    // 正文部分定义
    struct iovec msg_iov[1];
    msg_iov[0].iov_base = exitFlag;
    msg_iov[0].iov_len = sizeof(int);

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
    if (ret == 0)
    {
        *pfdtorecv = -1;
        free(msg_control);
        return 0;
    }

    printf("recv info = %ls, fd = %d\n", exitFlag, *(int *)CMSG_DATA(msg_control));
    *pfdtorecv = *(int *)CMSG_DATA(msg_control);

    free(msg_control);
    return ret;
}