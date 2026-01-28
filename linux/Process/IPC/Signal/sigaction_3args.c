#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <errno.h>


/**
 * int sigaction (
 *      int signum,                     //信号种类
 *      const struct sigaction *act,    //传入参数：新的行为     
 *      struct sigaction *oldact        //传出参数：获取旧的行为，为NULL则不获取
 *  )
 * 
 * struct sigaction {   
 *      void (*sa_handler)(int);
 *      void (*sa_sigaction)(int, siginfo_t *, void *);
 *      sigset_t   sa_mask;         //额外临时屏蔽信号
 *      int     sa_flags;           //信号处理方式
 *      void    (*sa_restorer)(void);
 *  }
 * 
 * sa_mask信号位图操作:
 *      int sigemptyset(sigset_t *set); //初始化信号位图--移除所有信号
 *      int sigfillset(sigset_t *set);  //初始化信号位图--添加所有信号
 *      int sigaddset(sigset_t *set, int signum);   //添加1个信号
 *      int sigdelset(sigset_t *set, int signum);   //删除1个信号
 *      int sigismember(const sigset_t *set, int signum);   //判断1个信号是否在信号位图中
 * sa_flags信号处理方式:
 *      SA_RESTART   //重启信号处理函数
 *      SA_NODEFER   //临时屏蔽信号
 *      SA_RESETHAND   //注册一次生效一次
 *      SA_NOCLDSTOP   //忽略子进程停止信号
 */

void sig_handler(int signum, siginfo_t *siginfo, void *ucontext)    //三个参数设置
{
    printf("signum = %d, uid = %d\n", signum, siginfo->si_uid);
    printf("Current process UID = %d, EUID = %d\n", getuid(), geteuid());
}

int main(int argc, char *argv[])
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));

    act.sa_sigaction = sig_handler;   //设置信号处理函数，注意：使用sa_sigaction字段而不是sa_handler字段
    act.sa_flags = SA_RESTART | SA_SIGINFO;  //sa_flags必须设置SA_SIGINFO以使用sa_sigaction字段

    sigemptyset(&act.sa_mask);  //清空信号临时屏蔽信号集
    sigaddset(&act.sa_mask, SIGQUIT);   //添加信号临时屏蔽信号，信号3

    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);

    char buf[1024] = {0};
    ssize_t sret = read(STDIN_FILENO, buf, sizeof(buf));
    printf("read ret = %zd, buf = %s\n", sret, buf);

    return 0;
}