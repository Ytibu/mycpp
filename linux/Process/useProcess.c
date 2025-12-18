#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void test1(){
    system("ping -c 4 baidu.com");
    //底层实现为fork()
}

void test2(){

    pid_t ret = fork(); //父进程返回子进程id, 子进程为0
    if(ret == 0){
        printf("this is child process\n");
        printf("pid is %d, ppid is %d\n",getpid(),getppid());

    }else{
        sleep(1);
        printf("this is father process\n");
        printf("pid is %d, ppid is %d\n",getpid(),getppid());
    }
}

//fork()前后的数据问题
void test3(){

}

//execv\execl: 执行新的程序
void test4(){

    printf("will fork: \n");
    pid_t ret = fork();
    if(ret > 0){
        
        printf("this is father process\n");
        printf("pid is %d, ppid is %d\n",getpid(),getppid());

        int fresult = execl("./myexec","./myexec","hello",NULL);  //传入程序路径，程序命令行运行参数(最后一个为NULL)
        if(fresult < 0){
            perror("execl");
        }

    }else if(ret == 0){
        printf("this is child process\n");
        printf("pid is %d, ppid is %d\n",getpid(),getppid());

        char * arr[] = {"./myexec","hello",NULL};  //创建一个字符串数组: 程序运行的命令行参数(最后一个为NULL)
        sleep(1);
        int result = execv("./myexec",arr);    //传入创建的数组和程序路径
        if(result == -1){
            perror("execv");
        }
    }else{
        perror("fork");
        return;
    }
}

//wait()等待子进程结束
void test5(){

    /**
     * 父进程提前终止，子进程继续运行，最终子进程的父进程为init，init最终回收资源 -- 孤儿进程
     * 父进程一直存在，子进程提前终止，最终子进程必须经由父进程的wait或waitpid回收资源 -- 僵尸进程
     */

    
    int wstatus;

    pid_t ret = fork();
    if(ret > 0){
        
        printf("this is father process\n");
        printf("pid is %d, ppid is %d\n",getpid(),getppid());

        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            printf("exit status = %d\n",WEXITSTATUS(wstatus));
        }else if(WIFSIGNALED(wstatus)){
            printf("abnormal quit, terminal signal = %d\n", WTERMSIG(wstatus));
        }


    }else if(ret == 0){

        sleep(2);
        printf("this is child process\n");
        printf("pid is %d, ppid is %d\n",getpid(),getppid());
        exit(1);

    }else{
        perror("fork");
    }
}

int main(){

    test5();

}