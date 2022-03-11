/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:22 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/12 00:09:20 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_boolean create_threads(t_philo *philo, t_boolean bool)
{
    int i;
    t_philo *philo_current;

	philo_current = philo->first;
    i = 2;
    if (bool == TRUE)
		i = 1;
	else
        philo_current = philo->first->next;
    while(i <= philo_current->node->n_philos)
    {
        if(pthread_create(&philo_current->thread, NULL, &threads, (void *)philo_current))
            return (FALSE);
        i += 2;
        if(i <= philo_current->node->n_philos)
            philo_current = philo_current->next->next;
    }
    return (TRUE);
}

t_boolean run_philos(t_philo *philo)
{
    if(philo->first != NULL)
	{ 
        if(!create_threads(philo, TRUE))
            return (FALSE);
        usleep(500);
        if(!create_threads(philo, FALSE))
            return (FALSE);
    }else {
		printf("\n la lista se encuentra vacia\n\n");
	}
    return (TRUE);
}