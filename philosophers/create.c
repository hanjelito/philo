/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:43:08 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/01 16:56:43 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philo(t_node *node, int index)
{
	t_philo *new;

	new			= malloc(sizeof(t_philo));
	new->id		= index;
	new->create_at = get_time();
	new->start = 0;
	new->end = 0;
	new->eat	= node->eat;
	new->sleep	= node->slpeep;
	new->n_eats	= node->n_eats;
	new->die	= node->die;
	pthread_mutex_init(&new->fork, NULL);
	pthread_mutex_init(&new->message, NULL);
	new->status = 0;
	if(node->philo.first == NULL)
	{
		node->philo.first			= new;
		node->philo.first->next	= node->philo.first;
		node->philo.last			= new;
		node->philo.first->prev = node->philo.last;
	}
	else
	{
		node->philo.last->next = new;
		new->next			= node->philo.first;
		new->prev			= node->philo.last;
		node->philo.last	= new;
		node->philo.first->prev = node->philo.last;
	}
}
