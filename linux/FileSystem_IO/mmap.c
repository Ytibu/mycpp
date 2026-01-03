#include <Cfun.h>

/*
    void *mmap (void *__addr, size_t __len, int __prot, int __flags, int __fd, __off_t __offset)    //映射文件
    int munmap (void *__addr, size_t __len) //取消映射
*/


/* 映射文件: 先创建文件，再截断文件，再映射文件，防止内存操作文件越界 */
void test_mmap(const char *file)
{

    int fd = open(file, O_RDWR | O_TRUNC, 0644);
    ERROR_CHECK_(fd, -1, "open");
    write(fd, "hello world", 11);

    ftruncate(fd, 12);

    char *p = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK_(p, MAP_FAILED, "mmap");

    for (int i = 0; i < 12; ++i)
    {
        printf("%c", p[i]);
        if (p[i] >= 'a' && p[i] <= 'z')
        {
            p[i] -= 32;
        }
    }
    printf("\n");

    p[11] = '\n';

    munmap(p, 12);
    close(fd);
}

int main(int argc, char *argv[])
{

    test_mmap("mmap.txt");

}