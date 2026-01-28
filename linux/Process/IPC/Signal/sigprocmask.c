#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

/**
 * int sigprocmask(
 *      int how,
 *      const sigset_t *set,
 *      sigset_t *oldset
 * );
 *  how:
 *      SIG_BLOCK: 屏蔽set中的信号
 *      SIG_UNBLOCK: 解除屏蔽set中的信号
 *      SIG_SETMASK: 将当前信号屏蔽字设置为set
 * 利用sigprocmask函数可以屏蔽或解除屏蔽某些信号
 */
void sig_handler(int signo)
{
    printf("catch signal %d\n", signo);
}

int main(int argc, char *argv[])
{
    signal(SIGINT, sig_handler);

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);

    sleep(5);

    sigset_t pending;
    sigpending(&pending);
    if (sigismember(&pending, SIGINT))
    {
        printf("pending SIGINT\n");
    }
    else
    {
        printf("no pending SIGINT\n");
    }

    sigprocmask(SIG_UNBLOCK, &set, NULL);

    char buf[1024] = {0};
    int sret = read(0, buf, sizeof(buf));
    printf("read %d byte:  %s\n", sret, buf);

    return 0;
}