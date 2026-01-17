#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>

/**
 * syslog - log message to syslog
 *      void openlog(const char *ident, int option, int facility);
 *      void syslog(int priority, const char *format, ...);
 *      void closelog(void);
 */

void Daemon()
{
    // 新建会话
    if (fork())
    {
        exit(0);
    }
    setsid();

    // 关闭设备
    for (int i = 0; i < 1023; ++i)
    {
        close(i);
    }

    // 修改环境属性
    chdir("/");
    umask(0);
}

int main(int argc, char **argv)
{
    Daemon();
    syslog(LOG_INFO, "Daemon started"); // 写入到系统日志：/var/log/syslog中
    for (int i = 0; i < 20; ++i)
    {
        syslog(LOG_INFO, "Daemon running,  i = %d\n", i);
        time_t ttime;
        time(&ttime);
        struct tm *pTm = gmtime(&ttime);
        syslog(LOG_INFO, "%d %04d:%02d:%02d", i, (1900 + pTm->tm_year), (1 + pTm -> tm_mon), (pTm->tm_mday));
        sleep(2);
    }

    return 0;
}