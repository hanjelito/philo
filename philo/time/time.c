/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 14:04:28 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/13 14:11:54 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_time.h"

static unsigned long	time_to_ms(struct timeval time)
{
	unsigned long	sec_to_ms;
	unsigned long	t_ms;

	sec_to_ms = time.tv_sec * 1000;
	t_ms = sec_to_ms + time.tv_usec / 1000;
	return (t_ms);
}

void	ft_leep_ms(unsigned int milliseconds)
{
	unsigned long	time;
	unsigned long	init_time;

	init_time = t_get_ms();
	time = t_get_ms();
	while ((time - init_time) < milliseconds)
	{
		time = t_get_ms();
		usleep(300);
	}
}

unsigned long	t_get_ms(void)
{
	struct timeval	time;
	unsigned long	time_ms;

	gettimeofday(&time, NULL);
	time_ms = time_to_ms(time);
	return (time_ms);
}

static unsigned long	ft_number_positive(long num)
{
	if (num < 0)
		return (-num);
	return (num);
}

long	t_diff_ms(unsigned long t1, unsigned long t2)
{
	long	diff;

	diff = ft_number_positive(t1 - t2);
	return (diff);
}
