#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*父进程创建子进程并负责对子进程的资源回收
子进程直接利用exec函数执行ls命令*/

int main(int argc, char *argv[])
{

    if(fork()){
        wait(NULL);
    }else{
        char *const args[] = {"./my_ls.out", "./", NULL};
        execv("my_ls.out", args);
    }
    
    return 0;
}