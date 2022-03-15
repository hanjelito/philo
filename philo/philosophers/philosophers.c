/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:38:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/15 14:30:46 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_node(t_node *node, char **argv)
{
	node->n_philos = ft_atoi(argv[1]);
	node->die = ft_atoi(argv[2]);
	node->eat = ft_atoi(argv[3]);
	node->slpeep = ft_atoi(argv[4]);
	node->n_eats = 0;
	node->n_eats_total = 0;
	node->id_dead = 0;
	if (argv[5])
		node->n_eats = ft_atoi(argv[5]);
	pthread_mutex_init(&node->message, NULL);
	node->philo = malloc(sizeof(t_philo));
	node->philo->first = NULL;
	node->philo->last = NULL;
	node->philo->next = NULL;
	node->philo->prev = NULL;
}

t_boolean	join_philos(t_philo *philo)
{
	int		i;
	t_philo	*philo_current;

	philo_current = philo->first;
	i = 0;
	while (i <= philo_current->node->n_philos)
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
		philo_current = philo_current->next;
		i++;
	}
	pthread_mutex_destroy(&philo_current->node->message);
	return (TRUE);
}

static void max_eas(t_philo *philo)
{
	int i;
	int n_eats;
	t_philo *philo_current;
	
	philo_current = philo->first;
	i = 0;
	n_eats = 0;
	while(i < philo_current->node->n_philos)
	{
		if(philo_current->n_eats >= philo_current->node->n_eats)
			n_eats++;
		i++;
		philo_current = philo_current->next;
	}
	if(n_eats >= philo_current->node->n_philos)
		philo_current->node->id_dead = TRUE;
}

void	philo_activity(t_philo *philo)
{
	t_philo			*philo_current;

	philo_current = philo->first;
	while (1)
	{
		max_eas(philo);
		philo_current->t_variable_eat_ms
			= t_diff_ms(philo_current->t_last_eat_ms, t_get_ms());
		if (philo_current->node->id_dead == TRUE)
			break ;
		if (philo_current->t_variable_eat_ms
			> (unsigned long)philo_current->node->die)
		{
			pthread_mutex_lock(&philo_current->node->message);
			philo_current->node->id_dead = TRUE;
			printf("%lu %d died\n",
				philo_current->t_variable_eat_ms, philo_current->id);
			pthread_mutex_unlock(&philo_current->node->message);
			break ;
		}
		philo_current = philo_current->next;
	}
}
