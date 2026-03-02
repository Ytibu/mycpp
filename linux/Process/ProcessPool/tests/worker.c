#include "head.h"

int makeWorker(int workerNum, workerdata_t *workerArr)
{
    for(int i = 0; i < workerNum; ++i){
        pid_t pid = fork();
        if(pid < 0){
            perror("fork");
            exit(1);
        }else if(pid == 0){
            //子进程
            while(1){
                sleep(1);
            }
        }else{
            //父进程
            workerArr[i].pid = pid;
            workerArr[i].status = FREE;
        }
    }

    return 0;
}