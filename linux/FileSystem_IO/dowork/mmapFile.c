#include <Cfun.h>

//利用mmap映射文件直接对磁盘文件进行操作(大写转换为小写，符号转换为空格)

int main(int argc, const char* argv[])
{
    /* 参数检验 */
    if(argc != 2){
        printf("argc error\n");
        return -1;
    }

    /* 文件打开 */
    int fd = open(argv[1], O_RDWR);
    if(fd == -1){
        perror("open");
        return -1;
    }

    /* 获取文件实际大小 */
    struct stat file_stat;
    if(fstat(fd, &file_stat) == -1){
        perror("fstat");
        close(fd);
        return -1;
    }
    
    off_t file_size = file_stat.st_size;
    int size = file_size + 10;

    /* 扩展文件大小，以防文件操作超越边界*/
    ftruncate(fd, size);

    /* 映射文件 */
    char *p = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == MAP_FAILED){
        perror("mmap");
        return -1;
    }

    /* 逐个字符转换*/
    for(int i = 0; i < size; ++i){
        if(p[i] > 'A' && p[i] < 'Z'){
            p[i] += 32;
        }else if(ispunct(p[i])){
            p[i] = ' ';
        }
    }

    /* 关闭 */
    munmap(p, size);
    close(fd);

    return 0;
}