/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:38:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/10 23:18:37 by juan-gon         ###   ########.fr       */
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
    int i;
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
        usleep(300);
    }
}

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

void deat_philo(t_philo *philo)
{   
    t_philo *current_philo;
    unsigned long t_current;

    t_current = get_time_ms();
    current_philo = philo->first;
    while(1)
    {
        current_philo->t_die  = time_diff_ms(current_philo->t_last_eat_ms, t_current);
        if(current_philo->node->die < current_philo->t_die)
        {
            current_philo->status = DEAD;
            current_philo->dead = current_philo->t_die;
            printf("%d muerto (%lu)\n", current_philo->id, current_philo->dead);
            break;
        }
        current_philo = current_philo->next;
    }
    
    // unsigned long t_current;

    // t_current = get_time_ms();
    // philo->t_die  = time_diff_ms(philo->t_last_eat_ms, t_current);
    // if(philo->node->die < philo->t_die)
    // {
    //     philo->status = DEAD;
    //     philo->dead = philo->t_die;
    // }
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
        deat_philo(philo);
    }else {
		printf("\n la lista se encuentra vacia\n\n");
	}
    return (TRUE);
}
