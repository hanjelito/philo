/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:22 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/10 23:26:15 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <time.h>

static void write_status(t_philo *philo)
{
    unsigned long t_curren_ms;
    unsigned long time_ms = get_time_ms();

    t_curren_ms = time_diff_ms(philo->node->time_initial_ms, time_ms);
    pthread_mutex_lock(&philo->message);
    if (philo->status == TAKE_FORK)
        printf("%lu %d has taken a fork\n", t_curren_ms, philo->id);
    else if (philo->status == EATING)
        printf("%lu %d is eating\n", t_curren_ms, philo->id);
    else if (philo->status == SLEEPING)
        printf("%lu %d is sleeping (%lu)\n", t_curren_ms, philo->id, philo->t_die);
    else if (philo->status == THINKING)
        printf("%lu %d is thinking (%lu)\n", t_curren_ms, philo->id, philo->t_die);
    pthread_mutex_unlock(&philo->message);
}

static void philo_eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork);
    philo->status = TAKE_FORK;
    write_status(philo);
    if(philo->id == philo->prev->id)
    {
        pthread_mutex_unlock(&philo->prev->fork);
        return ;
    }
    //
    pthread_mutex_lock(&philo->prev->fork);
    philo->status = TAKE_FORK;
    philo->t_last_eat_ms = get_time_ms();
    philo->t_die = 0;
    write_status(philo);
    if(philo->id == philo->prev->id)
    {
        return ;
    }
    philo->status = EATING;
    philo->node->n_eats++;
    write_status(philo);
    ft_msleep(philo->node->eat);
    //
    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&philo->prev->fork);
}

static void philo_sleep(t_philo *philo)
{
    philo->status = SLEEPING;
    write_status(philo);
    ft_msleep(philo->node->slpeep);
}

static void philo_think(t_philo *philo)
{
    philo->status = THINKING;
    write_status(philo);
}

void *threads(void *philo_current)
{
    t_philo *philo;

    philo = (t_philo *)philo_current;
    while(1)
    {
        if(philo->status == RUN || philo->status == THINKING)
            philo_eat(philo);
        else if(philo->status == EATING)
            philo_sleep(philo);
        else if(philo->status == SLEEPING)
            philo_think(philo);
    }
    return (NULL);
}