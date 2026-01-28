#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

/*查看看当前目录下的所有文件*/
int main(int argc, char *argv[])
{
    if(argc != 2){
        printf("argc error\n");
        exit(1);
    }

    DIR *dir = opendir(argv[1]);
    if(dir == NULL){
        perror("opendir");
        exit(1);
    }

    struct dirent *ptr;
    while((ptr = readdir(dir)) != NULL){
        printf("%s\n", ptr->d_name);
    }

    closedir(dir);
    
    return 0;
}