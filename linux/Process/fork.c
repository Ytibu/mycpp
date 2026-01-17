#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * fork()
 *   创建进程：创建子进程的task_struct结构体并设置pid，复制父进程的数据COW，设置返回值，运行子进程
 *      COW：写时复制，fork底层先不复制具体数据，当进程修改数据时，再复制数据
 */

 
int main(int argc, char *argv[]){

    pid_t ret = fork();
    // fork()后子进程返回值为0，父进程返回子进程id，错误返回负数
    if(ret){

        printf("this is father process\n");
        printf("pid is %d, ppid is %d\n",getpid(),getppid());
        sleep(1);

    }else if(ret == 0){
        
        printf("this is child process\n");
        printf("pid is %d, ppid is %d\n",getpid(),getppid());
    }else{
        perror("fork");
        exit(1);
    }


    return 0;
}