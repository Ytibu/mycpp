#include <Cfun.h>

/* 
    有名管道 namedpipe/FIFO 进程间通信，使用文件IO的方式进行操作
        1.创建管道: mkfifo pipe_name 创建一个类似于目录的文件
        2.管道通信: 单工通信，管道只能有一个读端和一个写端

    阻塞情况：
        1. write阻塞，管道读端没有数据时，read()会阻塞；
        2. read阻塞， 管道写端没有空间时，write()会阻塞；
        3. open阻塞， 管道两端没有打开时，open()会阻塞；

*/

void pipe_read(){
    
    int fd = open("mypipe", O_RDONLY);
    ERROR_CHECK_(fd, -1, "open");

    char buf[1024] = {0};
    int ret = read(fd, buf, sizeof(buf));

    printf("read %d bytes: %s\n", ret, buf);
}

void pipe_write(const char* words){

    int fd = open("mypipe", O_WRONLY);
    ERROR_CHECK_(fd, -1, "open");
   
    int ret = write(fd, words, strlen(words));

    printf("write %d bytes: %s\n", ret, words);

}

int main(int argc, char* argv[]) {

    ARGS_CHECK(argc, 2);
    if(strcmp(argv[1], "read") == 0){
        pipe_read();
    }else if(strcmp(argv[1], "write") == 0){
        pipe_write((char *)argv[2]);
    }else{
        printf("error args\n");
    }


}