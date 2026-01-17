#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

/*
    fork() 创建子进程，父进程和子进程都执行fork()之后的代码，
    父子进程的内核态空间数据是共享的：文件共享(同时操作文件描述符可能冲突，但可以借此进行通信)
    父子进程的用户态空间数据是独立的：栈空间、数据段、堆空间是完全隔离的(拷贝)。
*/

int dataSeg = 1;
int main(int argc, char *argv[])
{
    int stack = 2;
    int *pHeap = (int *)malloc(sizeof(int));
    *pHeap = 3;
    int fd = open("/tmp/demo.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    
    printf("hello ");

    if(fork()){
        sleep(1);
        printf("world\n");
        printf("Parent: dataSeg = %d, stack = %d, heap = %d\n", dataSeg, stack, *pHeap);
        write(fd, "world\n", 6);
        
    }else{
        dataSeg+= 3;
        stack += 3;
        *pHeap += 3;
        printf("world\n");
        printf("Child: dataSeg = %d, stack = %d, heap = %d\n", dataSeg, stack, *pHeap);
        write(fd, "hello ", 6);
        
    }

    return 0;
}