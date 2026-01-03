#include <Cfun.h>

int main(int argc, char* argv[]){

    FILE *fp =  fopen("a2.txt","r");
    ERROR_CHECK_(fp, NULL, "fopen");

    fwrite("hello world\n",1,12,fp);

    char buf[1024];
    fread(buf,1,sizeof(buf),fp);
    printf("buf = %s\n", buf);

    fclose(fp);
}