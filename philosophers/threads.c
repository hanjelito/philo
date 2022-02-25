/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:22 by juan-gon          #+#    #+#             */
/*   Updated: 2022/02/25 16:32:16 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <time.h>

void *threads(void *philo_current)
{
    int i;
    int fork1;
    int fork2;
    t_philo *philo;
    philo = (t_philo *)philo_current;
    i = 1;
    while(1)
    {
        pthread_mutex_lock(&philo->prev->fork);
        pthread_mutex_lock(&philo->fork);
        printf("philo %d  comiendo - nro de comidaj(%d)\n", philo->id, i);
        sleep(2);
        pthread_mutex_unlock(&philo->prev->fork);
        pthread_mutex_unlock(&philo->fork);
        if(i >= 10)
        {
            philo->status = 1;
            printf("--- murio %d\n", philo->id);
            break ;
        }
        ++i;
    }
    return (NULL);
}