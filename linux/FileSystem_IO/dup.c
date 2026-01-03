#include <Cfun.h>

/*
    int dup (int __fd)  //复制文件描述符
    int dup2 (int __fd, int __fd2)  //复制文件描述符
*/

/* 重定向文件描述符 */
void test_dup(const char *string)
{
    int oldfd = STDOUT_FILENO;

    int newfd = dup(oldfd);
    ERROR_CHECK_(newfd, -1, "dup");

    write(newfd, string, strlen(string));
    write(newfd, "\n", 1);

    close(newfd);
}

/* 重定向文件描述符2 */
void test_dup2(const char *file, const char *string)
{
    int oldfd = STDOUT_FILENO;
    int newfd = open(file, O_RDWR | O_TRUNC, 0644);
    ERROR_CHECK_(newfd, -1, "open");

    dup2(newfd, oldfd);

    write(oldfd, string, strlen(string));

    // close(oldfd);
    close(newfd);
}

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);
    test_dup((char*)argv[1]);
    test_dup2("demo.txt", (char*)argv[1]);

    return 0;
}