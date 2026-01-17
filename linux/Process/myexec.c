#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char* argv[]){
    printf("data is： %s\n",argv[1]);
    printf("pid is %d, ppid is %d\n",getpid(),getppid());
}