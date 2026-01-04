#include <Cfun.h>

//实现两个文件的二进制对比

/*
    逐内存对比，对比读取大小，对比内存，直到读取完后输出相同
    发现读取大小不一致，读取内存不一致，都直接输出不同
*/

int main(int argc, char *argv[])
{
    if(argc != 3){
        printf("argc Error\n");
        return -1;
    }

    int fd1, fd2;
    fd1 = open(argv[1], O_RDONLY);
    if(fd1 == -1){
        perror("open");
        return -1;
    }

    fd2 = open(argv[2], O_RDONLY);
    if(fd2 == -1){
        perror("open");
        close(fd1);
        return -1;
    }

    ssize_t ret1, ret2;
    char buf1[4096] = {0}, buf2[4096] = {0};
    while (1)
    {
        memset(buf1, 0, sizeof(buf1));
        memset(buf2, 0, sizeof(buf2));

        ret1 = read(fd1, buf1, sizeof(buf1));
        ret2 = read(fd2, buf2, sizeof(buf2));

        if(ret1 != ret2){
            printf("not same\n");
            break;
        }else if(memcmp(buf1, buf2, ret1) != 0){
            printf("not same\n");
            break;
        }else if(ret1 == 0){
            printf("same\n");
            break;
        }
    }

    close(fd1);
    close(fd2);

    return 0;
}