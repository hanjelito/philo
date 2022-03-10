#include "get_time.h"

static unsigned long	ft_abs(long n)
{
	if (n < 0)
		return (-n);
	return (n);
}

long	time_diff_ms(unsigned long time1, unsigned long time2)
{
	long	diff;

	diff = ft_abs(time1 - time2);
	return (diff);
}

static unsigned long	timeval_to_milliseconds(struct timeval time)
{
	unsigned long	ms_time;
	unsigned long	seconds_to_ms;

	seconds_to_ms = time.tv_sec * 1000;
	ms_time = seconds_to_ms + time.tv_usec / 1000;
	return (ms_time);
}

unsigned long	get_time_ms(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = timeval_to_milliseconds(time);
	return (time_ms);
}

void	ft_msleep(unsigned int milliseconds)
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
