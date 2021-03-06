/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:22 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/17 12:56:29 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	void	write_status(t_philo *philo)
{
	unsigned long	t_curren_ms;
	unsigned long	time_ms;

	time_ms = t_get_ms();
	pthread_mutex_lock(&philo->node->message);
	t_curren_ms = t_diff_ms(philo->node->time_initial_ms, time_ms);
	if (!philo->node->id_dead)
	{
		if (philo->status == TAKE_FORK)
			printf("%lu %d has taken a fork (%d)\n",
				t_curren_ms, philo->id, philo->n_eats);
		else if (philo->status == EATING)
		{
			philo->n_eats++;
			printf("%lu %d is eating (%d)\n",
				t_curren_ms, philo->id, philo->n_eats);
		}
		else if (philo->status == SLEEPING)
			printf("%lu %d is sleeping (%d)\n",
				t_curren_ms, philo->id, philo->n_eats);
		else if (philo->status == THINKING)
			printf("%lu %d is thinking (%d)\n",
				t_curren_ms, philo->id, philo->n_eats);
	}
	pthread_mutex_unlock(&philo->node->message);
}

static	void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo->status = TAKE_FORK;
	write_status(philo);
	if (philo->id == philo->prev->id)
	{
		pthread_mutex_unlock(&philo->fork);
		return ;
	}
	pthread_mutex_lock(&philo->prev->fork);
	philo->status = TAKE_FORK;
	write_status(philo);
	philo->status = EATING;
	philo->t_last_eat_ms = t_get_ms();
	write_status(philo);
	ft_leep_ms(philo->node->eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
}

static	void	philo_sleep(t_philo *philo)
{
	philo->status = SLEEPING;
	write_status(philo);
	ft_leep_ms(philo->node->slpeep);
}

static	void	philo_think(t_philo *philo)
{
	philo->status = THINKING;
	write_status(philo);
}

void	*threads(void *philo_current)
{
	t_philo	*philo;

	philo = (t_philo *)philo_current;
	while (philo->node->id_dead == FALSE)
	{
		if (philo->status == RUN || philo->status == THINKING)
			philo_eat(philo);
		else if (philo->status == EATING)
			philo_sleep(philo);
		else if (philo->status == SLEEPING)
			philo_think(philo);
	}
	return (NULL);
}
