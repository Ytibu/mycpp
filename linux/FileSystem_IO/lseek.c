#include <Cfun.h>

/*
    off_t lseek(int fd, off_t offset, int whence)
    fd:文件描述符；offset：正为向前偏移，负为向后偏移；whence：起始偏移位置；return 从文件开头的偏移量(-1错误)
    whence: SEEK_SET/SEEK_CUR/SEEK_END

    注意读写时：文件偏移是同步的，一个进行操作，另一个操作时起始位置也发生变化
    可以利用文件偏移修改文件大小，但是必须进行IO操作才能改变
*/


void test(){


    int fd = open("demo.txt", O_RDONLY);
    if(fd<0){
        perror("open");
        return;
    }

    //迁移到文件末尾向前偏移6
    off_t off1 = lseek(fd, -6, SEEK_END);
    if(off1<0){
        perror("lseek");
        return;
    }

    //将当前迁移位置到文件末尾的内容读取到buf中，打印buf内容
    char buf[1024] = {0};
    ssize_t size1 = read(fd,buf,sizeof(buf));
    if(size1<0){
        perror("read");
        return;
    }
    printf("demo.txt end6 is : %s\n",buf);


    //偏移到文件开头向后偏移10
    off_t off = lseek(fd, 10, SEEK_SET);
    if(off<0){
        perror("lseek");
        return;
    }

    //将当前偏移位置到文件末尾的内容读取到Buf中，然后打印
    ssize_t size = read(fd,buf,sizeof(buf));
    if(size<0){
        perror("read");
        return;
    }
    printf("demo.txt start10 to end: %s\n", buf);

    close(fd);

}


/* 改变文件大小的函数 */
void test1(){

    //将存在的文件，修改为指定的大小
    int ret = truncate("demo1.txt", 18);    //文件路径，修改后文件大小，变长用\o填充，变短舍弃
    if(ret<0){//正确返回0，错误返回-1
        perror("truncate");
        return;
    }

    //将一个文件描述符交给ftruncate，ftrucate将文件描述符对应的文件修改到指定大小
    int fd = open("demo2.txt", O_RDWR | O_CREAT,0664);
    if(fd<0){
        perror("open");
        close(fd);
        return;
    }
    int ret1 = ftruncate(fd, 1);    //文件描述符(打开文件才有)，修改后文件大小，变长用\o填充，变短舍弃
    if(ret1<0){//正确返回0，错误返回-1
        perror("ftruncate");
        return;
    }

    close(fd);
}

int main(){
    //test();
    test1();
}