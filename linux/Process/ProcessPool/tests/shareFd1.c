#include "head.h"

int main(int argc, char *argv[])
{
    int fds[2];
    pipe(fds);
    if (fork())
    {
        close(fds[0]);
        int fdfile = open("demo.txt", O_RDWR | O_CREAT, 0664);
        printf("main fdfile = %d\n", fdfile);
        write(fdfile, "hello", 5);
        write(fds[1], &fdfile, sizeof(fdfile));

        wait(NULL);
    }
    else
    {
        close(fds[1]);
        int fdfile;
        read(fds[0], &fdfile, sizeof(fdfile));
        printf("child fdfile = %d\n", fdfile);
        int ret = write(fdfile, "world!!!", 5);
        printf("ret = %d\n", ret);
    }

    return 0;
}