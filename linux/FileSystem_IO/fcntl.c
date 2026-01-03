#include <Cfun.h>

/*
    fcntl：文件控制函数,功能强大
    int fcntl(int fd, int cmd, ...);
*/

/* 设置文件阻塞状态 */
void test()
{

    int flags = fcntl(STDIN_FILENO, F_GETFL);
    if (flags < 0)
    {
        perror("F_GETFL");
        return;
    }
    flags |= O_NONBLOCK;

    int result = fcntl(STDIN_FILENO, F_SETFL);
    if (result < 0)
    {
        perror("F_SETFL");
        return;
    }

    char buf[1024] = {0};
tryagain:
    ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
    if (n < 0)
    {
        if (errno != EAGAIN)
        {
            perror("read /dev/tty");
            return;
        }
        sleep(1);
        // write(STDOUT_FILENO, buf, n);
        goto tryagain;
    }
    else
    {
        write(STDOUT_FILENO, buf, n);
    }
}

int main()
{
    test();
}