/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:13:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/07 00:33:10 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers/philosophers.h"



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
     return (0);
}