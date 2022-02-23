/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:38:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/02/23 19:16:27 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"




void proceos(t_node *node)
{
    imprimir(node);
}

void imprimir(t_node *node)
{
    pthread_mutex_lock(*(&node->print));
    write(1,"philo\n",6);
    pthread_mutex_unlock(*(&node->print));
}

void mutex_print(t_node *node)
{
    static pthread_mutex_t print;
    pthread_mutex_init(&print, NULL);
    node->print = &print;
}

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
            proceos(node);
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