#include <stdio.h>
#include <unistd.h>

void test(){

    int fds[2];
    pipe(fds);

    printf("fds[0]: %d, fds[1]: %d\n", fds[0], fds[1]);

    write(fds[1], "hello", 5);

    char buf[1024];
    read(fds[0], buf, sizeof(buf));

    printf("buf: %s\n", buf);

    close(fds[0]);
    close(fds[1]);
}

void test2(){

    int fds1[2];
    int fds2[2];
    pipe(fds1);
    pipe(fds2);

    if(fork()){
        close(fds1[1]);
    }else{
        close(fds1[0]);
    }
}

int main(int argc, char *argv[]){

    
    
}