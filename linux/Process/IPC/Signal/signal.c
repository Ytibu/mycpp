#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Signal信号
 *   
 * typedef void (*sighandler_t)(int);
 * sighandler_t signal(int signum, sighandler_t handler);   // 信号处理函数
 *      int signum ：信号编号; sighandler_t handler ：信号处理函数(参数为int signum, 返回值为void)
 * 
 */


void handler_signal(int signum)
{
    printf("Signal %d before\n", signum);
    sleep(5);
    printf("Signal %d after\n", signum);
}

int main(int argc, char *argv[])
{
    signal(SIGINT, handler_signal);
    signal(SIGQUIT, handler_signal);

    while (1)
    {
        sleep(1);
    }

    return 0;
}