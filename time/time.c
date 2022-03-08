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

unsigned long	get_time_ms(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	// creamos la fecha segundos tv_sec y los  microsegundos tv_usec
	gettimeofday(&time, NULL);
	// jutamos todo
	time_ms = get_time();
	return (time_ms);
}

void	usleep_time(unsigned int milliseconds)
{
	unsigned long	initial_time;
	unsigned long	time;

	initial_time = get_time_ms();
	time = get_time_ms();
	while ((time - initial_time) < milliseconds)
	{
		time = get_time_ms();
		usleep(300);
	}
}
