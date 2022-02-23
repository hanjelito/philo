/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:38:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/02/21 18:41:29 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void run_philos(t_node *node)
{
	t_philo *philo_current;
    pthread_t newthread;
    int i;

	philo_current = malloc(sizeof(t_philo));
	philo_current = node->philo.first;
	if(node->philo.first != NULL)
	{
        i = 0;
		while (i < node->n_philos)
		{
            pthread_create(&newthread, NULL, threads, (void *)philo_current);
			philo_current = philo_current->next;
            if(node->philo.first == philo_current)
                break ;
            i++;
		}
        pthread_join(newthread, NULL);
	} else
	{
		printf("\n la lista se encuentra vacia\n\n");
	}
    free(philo_current);
    philo_current = 0;
}

void init_node(t_node *node, int n_philos)
{
    node->n_philos = n_philos;
    node->philo.first = NULL;
    node->philo.last = NULL;
    node->philo.next = NULL;
    node->philo.prev = NULL;
} 