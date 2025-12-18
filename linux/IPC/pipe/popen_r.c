#include <stdio.h>

int main(){

    FILE *fp = popen("./printf","w");
    char buf[1024] = {0};
    fread(buf, 1, sizeof(buf), fp);
    printf("buf = %s", buf);
    pclose(fp);

}