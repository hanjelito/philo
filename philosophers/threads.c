/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:22 by juan-gon          #+#    #+#             */
/*   Updated: 2022/02/24 17:34:33 by juan-gon         ###   ########.fr       */
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
    while(1)
    {
        philo->status = 1;
        if(philo->prev->status == 0)
        {
            philo->prev->status = 1;
            pthread_mutex_lock(&philo->fork);
            pthread_mutex_lock(&philo->prev->fork);
            printf("philo %d  comiendo\n", philo->id);
            sleep(2);
            pthread_mutex_unlock(&philo->fork);
            pthread_mutex_unlock(&philo->prev->fork);
            philo->status = 0;
            philo->prev->status = 0;
            ++i;
        }
    }
    printf("--- murio %d\n", philo->id);
    return (NULL);
}