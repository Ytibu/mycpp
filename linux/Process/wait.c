#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * 父进程提前终止，子进程继续运行，最终子进程的父进程为init，init最终回收资源 -- 孤儿进程
 * 父进程一直存在，子进程提前终止，最终子进程必须经由父进程的wait或waitpid回收资源 -- 僵尸进程
 * __pid_t wait (int *wstatus);
 *  父进程阻塞等待子进程结束，返回子进程的pid，子进程的退出状态保存在wstatus中
 * 
 * 进程结束：return no; main函数退出，父进程回收资源
 *          exit(no); 父进程回收资源 _exit(no); 父进程不回收资源
 *          abort(); 进程自己调用abort推出本进程，父进程不回收资源
 * 
 */


int main(){

    int wstatus;

    pid_t ret = fork();
    if(ret){

        wait(&wstatus);

        printf("this is father process\n");
        printf("pid is %d, ppid is %d\n",getpid(),getppid());

        if(WIFEXITED(wstatus)){
            printf("exit status = %d\n",WEXITSTATUS(wstatus));
        }else if(WIFSIGNALED(wstatus)){
            printf("abnormal quit, terminal signal = %d\n", WTERMSIG(wstatus));
        }

    }else if(ret == 0){

        sleep(1);

        printf("this is child process\n");
        printf("pid is %d, ppid is %d\n",getpid(),getppid());
        exit(1);

    }else{
        perror("fork");
    }

    return 0;

}