#include <Cfun.h>

/*
    int	ftruncate(int fd, unsigned long length)
    //截断文件末尾，用二进制0补齐文件末尾
*/

/* 截断文件 */
void test_ftruncate(const char *file)
{
    int fd = open(file, O_RDWR);
    ERROR_CHECK_(fd, -1, "open");

    ftruncate(fd, 10);

    close(fd);
}

int main(int argc, char *argv[])
{
    test_ftruncate("file.txt");
    return 0;
}