#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * int sigpending(
 *      sigset_t *set
 * );
 * 利用sigpending函数可以获取当前进程的未决信号集
 */

void sig_hanler(int signum)
{
    printf("Before signum = %d\n", signum);
    sleep(5);
    sigset_t pending;
    sigpending(&pending);
    if (sigismember(&pending, signum))
    {
        printf("in the pending, signal = %d\n", signum);
    }
    else
    {
        printf("not in the pending, signal = %d\n", signum);
    }
    printf("After signum = %d\n", signum);
}

int main(int argc, char *argv[])
{
    signal(SIGINT, sig_hanler);

    char buf[1024] = {0};
    ssize_t sret = read(0, buf, sizeof(buf));
    printf("read %zd bytes, buf = %s\n", sret, buf);
    return 0;
}