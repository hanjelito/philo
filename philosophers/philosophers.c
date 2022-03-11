/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:38:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/12 00:45:45 by juan-gon         ###   ########.fr       */
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
    while(i <= philo_current->node->n_philos)
    {
        if (pthread_join(philo_current->thread, NULL))
        {
            write(1, "error\n", 6);
            return (FALSE);
        }
        philo_current = philo_current->next;
        i ++;
    }
    return (TRUE);
}

void philo_activity(t_philo *philo)
{
    t_philo *philo_current;
    
    philo_current = philo->first;
     while(1)
    {
        if(philo_current->status == DEAD)
        {
            printf("%lu %d died\n", philo_current->dead, philo_current->id);
            return ;
        }
        philo_current = philo_current->next;
        usleep(10);
    }
}