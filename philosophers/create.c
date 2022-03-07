/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:43:08 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/07 21:53:01 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philo(t_node *node, int index)
{
	t_philo *new;

	new = malloc(sizeof(t_philo));
	data_common(new, node, index);
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

void data_common(t_philo *new, t_node *node, int id)
{
	new->id			= id;
	new->create_at	= get_time();
	new->start		= 0;
	new->dead		= 0;
	new->t_die		= 0;
	new->eat		= node->eat;
	new->sleep		= node->slpeep;
	new->n_eats		= node->n_eats;
	new->die		= node->die;
	new->status		= RUN;
	new->node		= node;
	pthread_mutex_init(&new->fork, NULL);
	pthread_mutex_init(&new->message, NULL);
}
