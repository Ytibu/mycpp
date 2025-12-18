#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

/*
 * 系统调用头文件
 * #include <sys/shm.h>
 * 
 * int shmget(key_t key, size_t size, int shmflg);  // 创建物理共享内存
 * int shmat(int shmid, const void *shmaddr, int shmflg);  // 虚拟内存映射共享内存
 * int shmdt(const void *shmaddr);  // 删除虚拟内存映射
 * 
 * key 是共享内存的标识符，0/IPC_PRIVATE 表示创建一个私有的共享内存
 * size 是共享内存的大小
 * shmflg 是共享内存的属性，创建标志|权限标志：IPC_CREAT | 0666
*/



void test(){

    int shmid = shmget(0x1234, 1024, IPC_CREAT | 0666); // 创建共享内存

    if(shmid < 0){
        perror("shmget");
        return;
    }

    printf("shmid = %d\n", shmid);

    char *shmaddr = shmat(shmid, NULL, 0);
    if(shmaddr < 0){
        perror("shmat");
        return;
    }

    memcpy(shmaddr, "hello world", 11);
    printf("shmaddr = %s\n", shmaddr);

}

void test1(){ 

    int shmid = shmget(0x1238, 1024, IPC_CREAT | 0666);

    int *shmaddr = shmat(shmid, NULL, 0);

    *shmaddr = 100;

    int num = 1000000;
    if(fork()){
        for(int i = 0; i < num; ++i){
            ++*shmaddr;
        }
        wait(NULL);
        printf("shmaddr = %d\n", *shmaddr);
    }else{
        for(int i = 0; i < num; ++i){
            ++*shmaddr;
        }
    }

}

int main()
{
    test1(); 
}