#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * exec族：execl & execv
 *      int execl (const char *__path, const char *__arg, ...)
 *      int execv (const char *__path, char *const __argv[])
 *  两个函数：第一个参数必须为执行程序的命令，最后一个参数必须为NULL
 *      execl直接传入命令行参数
 *      execv直接传入命令行参数数组
 * 
 *  进程的数据替换来实现进程不变，但是进程内容改变
 */

int main(int argc, char* argv[])
{

    printf("will fork: \n");
    pid_t ret = fork();
    if(ret){
        
        sleep(1);
        printf("this is father process\n");

        int result = execl("./myexec.out","./myexec.out","hello",NULL);  //传入程序路径，程序命令行运行参数(最后一个为NULL)
        if(result < 0){
            perror("execl");
        }

    }else if(ret == 0){

        printf("this is child process\n");

        char* arr[] = {"./myexec.out","hello",NULL};  //创建一个字符串数组: 程序运行的命令行参数(最后一个为NULL)
        
        int result = execv("./myexec.out",arr);    //传入创建的数组和程序路径
        if(result < 0){
            perror("execv");
        }
    }else{
        perror("fork");
        exit(1);
    }

    return 0;
}