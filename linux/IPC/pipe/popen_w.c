#include <stdio.h>

int main(){

    FILE *fp = popen("./scanf","w");
    fwrite("5 6 ",1,3,fp);
    pclose(fp);

}