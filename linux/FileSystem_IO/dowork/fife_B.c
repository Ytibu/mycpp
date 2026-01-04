#include <Cfun.h>

int main(int argc, const char* argv[])
{
    if(argc!=2){
        printf("argc error\n");
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        perror("open");
        return -1;
    }

    char buf[1024] = {0};
    int ret = read(fd, buf, sizeof(buf));
    if(ret == -1){
        perror("read");
        return -1;
    }

    printf("read %ld bytes: %s\n",sizeof(buf),buf);

    return 0;
}