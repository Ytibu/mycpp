#include <Cfun.h>

// 利用系统调用完成一个文件拷贝

//通过read的返回值来决定写入的长度，直接使用strlen(根据指定内存向后读取到\0的位置)可能长度变短

int main(int argc, char *argv[]){

    /* 参数检验 */
    if(argc != 3){
        printf("Usage: %s source_file dest_file\n", argv[0]);
        return -1;
    }

    /* 文件打开 */
    int fd1, fd2;
    fd1 = open(argv[1], O_RDONLY);
    if(fd1 == -1){
        printf("open %s error\n", argv[1]);
        return -1;
    }

    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd2 == -1){
        printf("open %s error\n", argv[2]);
        close(fd1);
        return -1;
    }

    /* 文件拷贝 */
    ssize_t red_ret, write_ret;
    char buf[1024] = {0};
    while (1)
    {
        red_ret = read(fd1, buf, sizeof(buf));
        if(red_ret == 0){
            break;
        }else if(red_ret < 0){
            perror("read");
            close(fd1);
            close(fd2);
            return -1;
        }else{
            write_ret = write(fd2, buf, red_ret);
            if(write_ret < 0 || write_ret != red_ret){
                perror("write");
                close(fd1);
                close(fd2);
                return -1;
            }
            memset(buf, 0, sizeof(buf));
        }
    }

    close(fd1);
    close(fd2);
    
    return 0;
    
}