/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:22 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/08 01:13:57 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <time.h>

static void write_status(t_philo *philo)
{
    pthread_mutex_lock(&philo->message);
    if (philo->status == TAKE_FORK)
        printf("%lu %d has taken a fork\n", timeline(philo->create_at), philo->id);
    else if (philo->status == EATING)
        printf("%lu %d is eating (%d)\n", timeline(philo->create_at), philo->id, philo->eat);
    else if (philo->status == SLEEPING)
        printf("%lu %d is sleeping\n", timeline(philo->create_at), philo->id);
    else if (philo->status == THINKING)
        printf("%lu %d is thinking (%ld)\n", timeline(philo->create_at), philo->id, philo->t_die - philo->start);
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
    write_status(philo);
    philo->start = get_time();
    philo->status = EATING;
    write_status(philo);
    usleep_time(philo->eat);
    //
    pthread_mutex_unlock(&philo->fork);
    pthread_mutex_unlock(&philo->prev->fork);
}

static void philo_sleep(t_philo *philo)
{
    philo->status = SLEEPING;
    write_status(philo);
    usleep_time(philo->sleep);
}

static void philo_think(t_philo *philo)
{
    philo->status = THINKING;
    write_status(philo);
}

void deat_philo(t_philo *philo)
{   
    int t_dead;

    philo->t_die = get_time();
    t_dead  = philo->t_die - philo->start;
    if(philo->die < t_dead)
    {
        philo->status = DEAD;
        philo->dead = t_dead;
    }
}

void *threads(void *philo_current)
{
    t_philo *philo;

    philo = (t_philo *)philo_current;
    while(philo->n_eats == philo->node->n_eats)
    {
        if(philo->status == RUN || philo->status == THINKING)
            philo_eat(philo);
        else if(philo->status == EATING)
            philo_sleep(philo);
        else if(philo->status == SLEEPING)
            philo_think(philo);
        deat_philo(philo);
    }
    return (NULL);
}