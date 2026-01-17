#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * 会话：session, 一个或多个进程组组成的集合
 * 获取进程组ID，进程组ID，会话ID
 * 创建会话id：setsid()
 * 获取会话id：getpgid()
 */


int main(int argc, char **argv)
{
    if(fork()){
        printf("Parent: pid = %d, pgid = %d, sid = %d\n", getpid(), getpgid(0), getsid(0));
    }else{
        printf("Child: pid = %d, pgid = %d, sid = %d\n", getpid(), getpgid(0), getsid(0));
    }
    
    return 0;
}