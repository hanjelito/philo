/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:43:08 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/12 12:37:00 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void philo_common(t_philo *new, t_node *node, int id)
{
	new->id				= id;
	new->t_last_eat_ms	= node->time_initial_ms;
	new->n_eats		= 0;
	new->status		= RUN;
	new->t_variable_eat_ms = 0;
	new->node		= node;
	pthread_mutex_init(&new->fork, NULL);
	pthread_mutex_init(&new->message, NULL);
}

void	create_philo(t_node *node, int index)
{
	t_philo *new;

	new = malloc(sizeof(t_philo));
	philo_common(new, node, index);
	if(node->philo->first == NULL)
	{
		node->philo->first			= new;
		node->philo->first->next	= node->philo->first;
		node->philo->last			= new;
		node->philo->first->prev	= node->philo->last;
	}
	else
	{
		node->philo->last->next		= new;
		new->next					= node->philo->first;
		new->prev					= node->philo->last;
		node->philo->last			= new;
		node->philo->first->prev 	= node->philo->last;
	}
}


