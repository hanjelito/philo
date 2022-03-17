/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:13:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/17 12:53:09 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers/philosophers.h"

static void	philo_free(t_philo *philo)
{
	int		i;
	t_philo	*philo_current;

	i = 1;
	philo_current = philo->next;
	while (i < philo_current->node->n_philos)
	{	
		free(philo_current);
		philo_current = philo_current->next;
	}
	free(philo);
}

int	main(int argc, char **argv)
{
	int		i;
	t_node	*node;

	node = malloc(sizeof(t_node));
	if ((argc >= 5) && (argc <= 6))
	{
		node->time_initial_ms = t_get_ms();
		init_node(node, argv);
		i = 0;
		while (i < node->n_philos)
			create_philo(node, ++i);
		if (run_philos(node->philo) == FALSE)
			return (1);
		philo_activity(node->philo);
		if (join_philos(node->philo) == FALSE)
			return (1);
	}
	else
		printf("Error parameter philos\n");
	philo_free(node->philo);
	free(node);
	node = 0;
	return (0);
}
