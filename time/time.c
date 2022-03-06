#include "get_time.h"

long get_time(void)
{
    struct timeval timev;
    long            times;

    gettimeofday(&timev, NULL);
    times = (timev.tv_sec * 1000) + timev.tv_usec / 1000;
    return (times);
}

long timeline(long start)
{
    struct timeval timev;
    long            times;

    gettimeofday(&timev, NULL);
    times = (timev.tv_sec * 1000) + timev.tv_usec / 1000;
    return (times - start);
}

void  usleep_time(int time)
{
    long start;

    start = get_time();
    while(get_time() < start + time)
        usleep(10);
}