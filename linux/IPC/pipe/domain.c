#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>


/*标准管道*/
void test()
{

    /**
     * 库函数
     * #include <stdio.h>
     *
     * FILE *popen(const char *command, const char *type)
     * int pclose(FILE *stream)
     *
     * 创建进程，父子间存在一条管道
     * 父进程popen, 父进程写，子进程读
     */

    FILE *fp = popen("./scanf", "w"); // 开启无名管道
    fwrite("5 6 ", 1, 3, fp);         // 此文件流可以进行正常的读写
    pclose(fp);                       // 关闭管道
}

/*无名管道*/
void test1()
{

    /**
     * 系统调用
     * #include <unistd.h>
     *
     * int pipe(int pipefd[2])
     *
     * pipefd[2]数组，保存函数返回的两个文件描述符：fd[0]指向读端，fd[1]指向写端
     * 只能用于父子进程之间
     * 可以使用文件IO中的read和write进行读写
     * 内核空间中的内存段
     * 管道大小固定，管道写满数据时，将会阻塞写入
     */

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


/*有名管道*/
void test2()
{
    /*
     * #include <sys/types.h>
     * #include <sys/stat.h>
     * 
     * int mkfifo(const char *pathname, mode_t mode);
     * pathname: 文件名; mode: 权限
     * 
     * 创建成功返回0, 失败返回-1
     * 只读打开会阻塞，只有当其他进程只写打开同意管道才返回，打开操作以读写或只写打开不会阻塞
    */

    // 创建命名管道
    if (mkfifo("/tmp/myfifo", 0664) < 0)
    {
        perror("mkfifo");
    }

    // 打开命名管道
    int fd = open("/tmp/myfifo", O_WRONLY); // 或 O_WRONLY
}

int main()
{
    test2();
}