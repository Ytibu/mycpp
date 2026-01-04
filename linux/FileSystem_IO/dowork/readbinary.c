#include <Cfun.h>

//读取自定义的二进制文件


/*
    先自定义数据格式
    写入时：直接将数据作为一个Buf整体写入到文件中
    读取时：先明确数据格式的大小整体，整体读取到Buf中，然后对buf进行解读
*/

#define MAXCOUNT 3
typedef struct student {
    char name[64];
    ssize_t stuNo;
    int grade;
} studentInfo;

void studentInfo_write(const char* filePath, const studentInfo* students, int maxCount)
{
    /* 创建或覆盖文件 */
    int fd = open(filePath, O_RDWR | O_TRUNC | O_CREAT, 0664);
    if(fd == -1){
        perror("open");
        exit(1);
    }

    /* 整体读取写入到文件中*/
    ssize_t ret = write(fd, students, sizeof(studentInfo) * maxCount);
    if(ret == -1){
        perror("write");
        close(fd);
        exit(1);
    }

    close(fd);

}

void studentInfo_read(const char* filePath, int maxCount)
{
    /* 打开文件 */
    int fd = open(filePath, O_RDONLY);
    if(fd == -1){
        perror("open");
        exit(1);
    }

    /* 明确数据格式数据量，整体读取到数据格式确定的Buf中 */
    studentInfo read_stu[maxCount];  // 创建新的数组用于读取
    ssize_t ret = read(fd, read_stu, sizeof(studentInfo) * maxCount);
    if(ret == -1){
        perror("read");
        close(fd);
        exit(1);
    }

    /* 根据明确的数据量，读取数据 */
    for(int i = 0; i < maxCount; ++i){
        printf("Name: %s, StuNo: %ld, Grade: %d\n", 
               read_stu[i].name, read_stu[i].stuNo, read_stu[i].grade);
    }

    close(fd);

}

int main(int argc, const char* argv[])
{
    if(argc != 2){
        printf("argc error\n");
        return -1;
    }
    
    studentInfo stu[MAXCOUNT] = {
        {"tintin", 2024, 23},
        {"jee", 2023, 23},
        {"leeJe", 2024, 18}
    };

    studentInfo_write(argv[1], stu, MAXCOUNT);

    studentInfo_read(argv[1], MAXCOUNT);

    return 0;
}