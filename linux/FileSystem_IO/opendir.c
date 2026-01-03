#include <Cfun.h>

/* 
    DIR *opendir (const char *__name)
    int closedir (DIR *__dirp)

    struct dirent *readdir (DIR *__dirp)
    
    int telldir (DIR *__dirp)

*/

/* opendir-readdir-closedir */
void test()
{

    DIR *pdir = opendir("../FileSystem");
    ERROR_CHECK_(pdir, NULL, "opendir");

    struct dirent *pdirent;
    while ((pdirent = readdir(pdir)) != NULL)
    {
        if (pdirent->d_name[0] != '.')
        {
            printf("inode = %ld, name = %s\n",
                   pdirent->d_ino, pdirent->d_name);
        }
    }

    closedir(pdir);
}

/* telldir seekdir*/
void test1()
{
    DIR *pdir = opendir("/root/workSpace/learnAbout/mycpp/linux/Process");
    ERROR_CHECK_(pdir, NULL, "opendir");

    long loc;
    struct dirent *pdirent;
    while ((pdirent = readdir(pdir)) != NULL)
    {
        printf("inode = %ld, name = %s\n", pdirent->d_ino, pdirent->d_name);
        if (strcmp(pdirent->d_name, "..") == 0)
        {
            loc = telldir(pdir);
        }
    }
    //seekdir(pdir, loc);
    rewinddir(pdir);
    pdirent = readdir(pdir);
    printf("inode = %ld, name = %s\n", pdirent->d_ino, pdirent->d_name);

    closedir(pdir);
}

int main()
{

    test1();
}