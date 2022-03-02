/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:22 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/02 16:50:17 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <time.h>

void *threads(void *philo_current)
{
    int i;
    t_philo *philo;

    philo = (t_philo *)philo_current;
    i = 1;
    while(1)
    {
        pthread_mutex_lock(&philo->prev->fork);
        pthread_mutex_lock(&philo->fork);
        philo_dead(philo, i);
        philo_take_fork(philo, i);
        philo_eat(philo, i);
        
        pthread_mutex_unlock(&philo->prev->fork);
        pthread_mutex_unlock(&philo->fork);
        if((i >=  philo->n_eats) && (philo->n_eats > 0))
            break ;
        //
        pthread_mutex_lock(&philo->message);
        philo_sleeping(philo, i);
        pthread_mutex_unlock(&philo->message);
        //
        pthread_mutex_lock(&philo->message);
        philo_thinking(philo, i);
        pthread_mutex_unlock(&philo->message);
        ++i;
    }
    return (NULL);
}

void philo_take_fork(t_philo *philo, int i)
{
    philo->start = get_time();
    printf("[%ld] %d  has taken a fork 🍴(%d)\n", timeline(philo->create_at), philo->id, i);
    philo->status = TAKE_FORK;
}

void philo_eat(t_philo *philo , int i)
{
    printf("[%ld] %d  is eating 🍝(%d)\n", timeline(philo->create_at), philo->id, i);
    philo->status = EATING;
    usleep_time(philo->eat);
}

void philo_sleeping(t_philo *philo , int i)
{
    printf("[%ld] %d  is sleeping 😴(%d)\n", timeline(philo->create_at), philo->id, i);
    philo->status = SLEEPING;
    usleep_time(philo->sleep);
}

void philo_thinking(t_philo *philo , int i)
{
    printf("[%ld] %d  is thinking 🤯(%d)\n", timeline(philo->create_at), philo->id, i);
    philo->status = THINKING;
}

void philo_dead(t_philo *philo , int i)
{
    if(philo->status == THINKING)
    {
        int think;
        
        philo->end = get_time();
        think = (int)(philo->end - philo->start);
        printf("%d (%d)\n", think, philo->id);
        usleep_time(think);
        if (think >= philo->die)
        {
            printf("[%ld] %d  dead 🤯\n", timeline(philo->create_at), philo->id);
            philo->status = DEAD;
        }
        philo->start = 0;
        philo->end = 0;
    }
}