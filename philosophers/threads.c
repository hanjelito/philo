/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:45:22 by juan-gon          #+#    #+#             */
/*   Updated: 2022/02/21 13:03:19 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <time.h>

void *threads(void *philo_current)
{
    int i;
    int r = rand() % 10;
    t_philo *philo;

    philo = (t_philo *)philo_current;
    i = 0;
    while(i < r)
    {
        printf("entro %d - %d\n", i, philo->id);
        sleep(2);
        ++i;
    }
    printf("--\n");
    return (NULL);
}