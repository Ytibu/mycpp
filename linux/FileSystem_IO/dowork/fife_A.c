#include <Cfun.h>

int main(int argc, const char* argv[])
{
    if(argc!=2){
        printf("argc error\n");
        return -1;
    }

    int fd = open(argv[1], O_WRONLY);
    if(fd == -1){
        perror("open");
        return -1;
    }

    printf("hello world 1\n");

    int backfd = 10;
    dup2(STDOUT_FILENO, backfd);
    dup2(fd, STDOUT_FILENO);
    printf("hello world 2\n");

    dup2(backfd, STDOUT_FILENO);
    printf("hello world 3\n");

    return 0;
}