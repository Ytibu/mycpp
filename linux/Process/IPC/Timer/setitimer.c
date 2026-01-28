#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>


/**
 * 间隔定时器
 * 
 * int getitimer(int which, struct itimerval *curr_value);
 * int setitimer(int which, const struct itimerval *new_value,  
 *      struct itimerval *old_value);   
 * 
 * which:  ITIMER_REAL 墙上时钟   ITIMER_VIRTUAL  虚拟时钟，占用CPU时计时  ITIMER_PROF  
 * struct itimerval {
 *      struct timeval it_interval; // 间隔(第一次触发之后距离下一次的间隔时间)
 *      struct timeval it_value;    // 等待时间(经过此时间后，会触发一次定时器)
 *  }
 * 
 * 
 * 注意：墙上时钟与虚拟时钟的区别：墙上时钟根据真实的时间触发会持续占用CPU，虚拟时钟根据CPU时间触发只有当程序占用CPU时间才会触发。
 */

void timer_handler(int sig)
{
    time_t now = time(NULL);
    printf("timer_handler, now = %s\n",ctime(&now));
}

int main(int argc, char *argv[])
{
    signal(SIGALRM, timer_handler);

    struct itimerval itimer;
    itimer.it_interval.tv_sec = 1;
    itimer.it_interval.tv_usec = 0;
    itimer.it_value.tv_sec = 3;
    itimer.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &itimer, NULL);
    timer_handler(0);

    while (1) {
        
    }

    return 0;
}