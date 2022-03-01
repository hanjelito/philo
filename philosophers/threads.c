/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:22 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/01 12:04:24 by juan-gon         ###   ########.fr       */
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
        philo_take_fork(philo, i);
        philo_eat(philo, i);
        pthread_mutex_unlock(&philo->prev->fork);
        pthread_mutex_unlock(&philo->fork);
        if((i >=  philo->n_eats) && (philo->n_eats > 0))
        {
            philo->status = DEAD;
            printf("--- ultima comida %d\n", philo->id);
            break ;
        }
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
    if(philo->status == TAKE_FORK)
    {
        printf("[%ld] %d  has taken a fork 🍴(%d)\n", timeline(philo->create_at), philo->id, i);
        philo->status = EATING;
    }
}

void philo_eat(t_philo *philo , int i)
{
    if(philo->status == EATING)
    {
        printf("[%ld] %d  is eating 🍝(%d)\n", timeline(philo->create_at), philo->id, i);
        philo->status = SLEEPING;
        usleep_time(200);
    }
}

void philo_sleeping(t_philo *philo , int i)
{
    if(philo->status == SLEEPING)
    {
        printf("[%ld] %d  is sleeping 😴(%d)\n", timeline(philo->create_at), philo->id, i);
        philo->status = THINKING;
        usleep_time(300);
    }
    
}

void philo_thinking(t_philo *philo , int i)
{
    if(philo->status == THINKING)
    {
        printf("[%ld] %d  is thinking 🤯(%d)\n", timeline(philo->create_at), philo->id, i);
        philo->status = TAKE_FORK;
        usleep_time(300);
    }
}
