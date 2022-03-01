/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:38:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/01 17:17:28 by juan-gon         ###   ########.fr       */
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
    node->philo.first = NULL;
    node->philo.last = NULL;
    node->philo.next = NULL;
    node->philo.prev = NULL;
} 

void run_philos(t_node *node)
{
	t_philo *philo_current;
    pthread_t newthread[node->n_philos];
    int i;

	philo_current = malloc(sizeof(t_philo));
	philo_current = node->philo.first;
    philo_current->status = 0;

    if(node->philo.first != NULL)
	{
        i = 0;
        while(i < node->n_philos)
        {
            pthread_create(newthread+i, NULL, &threads, (void *)philo_current);
            philo_current = philo_current->next;
            i++;
        }
        i = 0;
        while(i < node->n_philos)
        {
            if(!pthread_join(newthread[i], NULL))
                break ;
            i++;
        }
        while(i > 100)
        {
            printf("hola\n");
            i++;
        }
    }else {
		printf("\n la lista se encuentra vacia\n\n");
	}
    free(philo_current);
    philo_current = 0;
}