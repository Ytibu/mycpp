#include <Cfun.h>

/*
    int fileno (FILE *__stream) //返回文件描述符所对应的文件
*/

/* 可以通过文件流获取文件描述符，从而直接进行文件IO操作 */
void test_fileno(const char *file)
{

    FILE *fp = fopen(file, "r");
    ERROR_CHECK_(fp, NULL, "open");

    printf("%d ", fileno(stdin));
    printf("%d ", fileno(stdout));
    printf("%d ", fileno(stderr));
    printf("%d\n", fileno(fp));
}

int main(int argc, const char* argv[])
{
    test_fileno("demo.txt");
}