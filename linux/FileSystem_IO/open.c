#include <Cfun.h>

/*
    int open(const char *pathname, int flags);  //选择打开模式，返回文件描述符
    int open(const char *pathname, int flags, ...mode_t mode ); //选择打开模式并指定创建文件的权限，返回文件描述符
    int close(int fd);  //关闭文件描述符

    ssize_t read  (int fd, void buf[.count], size_t count); //读取文件描述符fd中的数据，返回实际读取的字节数
        fd：文件描述符，buf：数据存取缓冲区，count：缓冲区大小；return: -1错误，读取字节数
    ssize_t write (int __fd, const void *__buf, size_t __n) //将数据写入文件描述符fd，返回实际写入的字节数
        fd：文件描述符，buf: 待读取缓冲区，count：数据大小；return -1错误，写入字节数

*/


/* 系统调用：文件操作：打开关闭，读写 */
void test(){

    int fd = open("test.txt", O_RDWR | O_CREAT, 0664);
    ERROR_CHECK(fd,"open");

    char buf[10] = {0};
    char *buff = "hello world\n";
    

    ssize_t size = write(fd, buff, strlen(buff)-1);

    lseek(fd,0, SEEK_SET);
    ssize_t size1;
    while( (size1 = read(fd, buf, sizeof(buf))) ){
        ERROR_CHECK(size1, "read");
        
        printf("file is %s\n", buf);
        memset(buf,0,sizeof(buf));
    }
    

    close(fd);

}

int main(){

    test();
}