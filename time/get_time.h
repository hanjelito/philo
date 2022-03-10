#ifndef GET_TIME_H
#define GET_TIME_H

#include "../utils/libft.h"
#include "../philosophers/philosophers.h"


// long    get_time(void);
void	ft_msleep(unsigned int milliseconds);
unsigned long	get_time_ms(void);
long	time_diff_ms(unsigned long time1, unsigned long time2);

#endif