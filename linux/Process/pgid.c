#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * 进程管理：一个或多个进程组成一个进程组，进程组ID为进程组内第一个进程的进程组ID
 * 获取进程组ID：getpgid(pid)
 */

int main(int argc, char *argv[])
{
	if(fork()){
        printf("parent, pid = %d, pgid = %d, ppid = %d, ppid->pgid = %d\n",
             getpid(), getpgid(0), getppid(), getpgid(getppid()));

        wait(NULL);
    }else{
        printf("child, pid = %d, pgid = %d, ppid = %d, ppid->pgid = %d\n",
             getpid(), getpgid(0), getppid(), getpgid(getppid()));
    }

	return 0;   
}