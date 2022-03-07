/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:13:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/07 20:42:50 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers/philosophers.h"

void free_node(t_philo *philo)
{
    t_philo *temp;
    int i;

    i = 0;    
    temp = philo->first;
    while(i < temp->node->n_philos)
    {
        free(temp);
        temp = philo->next;
        i++;
    }
    free(philo);
}

int main(int argc, char **argv)
{
    int i;
    int n_philos;
    t_node     *node;

    if(argc >= 5 && argc <= 6)
    {
        node = malloc(sizeof(t_node));
        n_philos = ft_atoi(argv[1]);
        init_node(node, argv);
        i = 0;
        while(i < n_philos)
            create_philo(node, ++i);
        if(run_philos(node->philo) == FALSE)
            return (1);
        philo_activity(node->philo);
        if(join_philos(node->philo) == FALSE)
            return (1);
    } else {
        printf("error\n");
    }
    // free_node(node->philo);
    free(node);
    node = 0;
    return (0);
}