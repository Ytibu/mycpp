#include <Cfun.h>

/* 修改文件权限：chmod*/
void test(){
    int ret = chmod("demo.txt", 0644);
    ERROR_CHECK_(ret, -1, "chmod");
}

/* 获取当前目录: getcwd
传入buf，和buf大小，函数将指针指向值区域，返回buf
*/
void test1(){

    char buf[1024] = {0};

    getcwd(buf, 1024);
    ERROR_CHECK_(buf,NULL,"getcwd");
    printf("current cwd is: %s\n", buf);

}

/* 改变目录: chdir，当程序结束后进程结束，最终会回到创建进程时的目录*/
void test2(){

    test1();
    int ret = chdir("/usr/include/");
    ERROR_CHECK(ret, "chdir");
    test1();
}

/* 创建目录: mkdir*/
void test3(){

    int ret = mkdir("demo", 0666);  // 创建目录的权限会受到umask影响，mode & ~umask
    ERROR_CHECK(ret, "mkdir");
}

/* 删除目录: rmdir*/
void test4(){

    int ret = rmdir("demo");
    ERROR_CHECK(ret, "rmdir");
}



int main(){

    test4();

}