/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:25:03 by juan-gon          #+#    #+#             */
/*   Updated: 2022/02/25 11:58:49 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../utils/libft.h"

typedef enum	e_status
{
	TAKE_FORK,
	EATING,
	THINKING,
	SLEEPING,
	DEAD
}				t_status;

typedef struct  s_philo
{
    int id;
    int status;
    pthread_mutex_t	fork;
    struct s_philo *next;
    struct s_philo *prev;
    struct s_philo *first;
    struct s_philo *last;
}               t_philo;

typedef struct  s_node
{
    int n_philos;
    struct s_philo philo;
}               t_node;

void    create_philo(t_node *node, int index);
void    *threads(void *philo_current);
void    run_philos(t_node *node);
void    init_node(t_node *node, int n_philos);

#endif