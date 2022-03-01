/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:13:06 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/01 12:21:04 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers/philosophers.h"

int main(int argc, char **argv)
{
    t_node     *node;
    int i;
    int n_philos;

    if(argc >= 5 && argc <= 6)
    {
        n_philos = ft_atoi(argv[1]);
        i = 0;
        node = malloc(sizeof(t_node));
        init_node(node, argv);
        while(i < n_philos)
            create_philo(node, ++i);
        run_philos(node);
    } else {
        printf("error\n");
    }

     return (0);
}