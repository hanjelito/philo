/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:22 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/05 01:00:11 by juan-gon         ###   ########.fr       */
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
    while(TRUE)
    {
        pthread_mutex_lock(&philo->prev->fork);
        pthread_mutex_lock(&philo->fork);
        philo->status = TAKE_FORK;
        printf("[%ld] %d  has taken a fork 🍴(%d)\n", timeline(philo->create_at), philo->id, i);
        pthread_mutex_unlock(&philo->prev->fork);
        pthread_mutex_unlock(&philo->fork);
        sleep(1);
        //
        pthread_mutex_lock(&philo->message);
        philo->status = EATING;
        sleep(1);
        printf("[%ld] %d  has taken a fork 🍴(%d)\n", timeline(philo->create_at), philo->id, i);
        pthread_mutex_unlock(&philo->message);
        ++i;
    }
    return (NULL);
}