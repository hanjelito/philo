/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:38:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/12 12:43:27 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_node(t_node *node, char **argv)
{
    node->n_philos = ft_atoi(argv[1]);
    node->die = ft_atoi(argv[2]);
    node->eat = ft_atoi(argv[3]);
    node->slpeep = ft_atoi(argv[4]);
    node->n_eats = 0;
    node->id_dead = 0;
    if(argv[5])
        node->n_eats = ft_atoi(argv[5]);
    node->philo = malloc(sizeof(t_philo));
    node->philo->first = NULL;
    node->philo->last = NULL;
    node->philo->next = NULL;
    node->philo->prev = NULL;
}


t_boolean join_philos(t_philo *philo)
{
    int i;
    t_philo *philo_current;

    philo_current = philo->first;
    i = 0;
    while(i <= philo_current->node->n_philos)
    {
        if (pthread_join(philo_current->thread, NULL))
            return (FALSE);
        philo_current = philo_current->next;
        i ++;
    }
    i = 0;
    while (i < philo_current->node->n_philos)
	{
		pthread_mutex_destroy(&philo_current->fork);
		pthread_mutex_destroy(&philo_current->message);
        philo_current = philo_current->next;
		i++;
	}
    return (TRUE);
}

void philo_activity(t_philo *philo)
{
    t_philo *philo_current;
    
    philo_current = philo->first;
    while(1)
    {
        if(philo_current->t_variable_eat_ms > philo_current->node->die)
        {
            philo_current->node->id_dead = philo_current->id;
            break ;
        }
        philo_current = philo_current->next;
    }
    ft_msleep(300);
    printf("%lu %d died\n", philo_current->t_variable_eat_ms, philo_current->id);
}