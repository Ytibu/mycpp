#include <stdio.h>

int main(int argc, char* argv[]){

    FILE *fp =  fopen("a2.txt","w+");
    if(fp == NULL){
        perror("fopen");
        return -1;
    }

    char buf[1024] = {};
    fread(buf,1,sizeof(buf),fp);
    printf("buf = %s\n", buf);
}