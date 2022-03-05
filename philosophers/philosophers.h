/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:25:03 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/05 09:59:50 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include "../utils/libft.h"
#include "../time/get_time.h"

typedef enum	e_status
{
    RUN,
	TAKE_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
}				t_status;

typedef enum e_boolean
{
    FALSE,
    TRUE
}           t_boolean;

typedef struct  s_philo
{
    int id;
    int eat;
    int sleep;
    int die;
    int n_eats;
    int status;
    long create_at;
    long start;
    long end;
    struct s_node	*node;
    pthread_mutex_t	message;
    pthread_t thread;
    pthread_mutex_t	fork;
    struct s_philo *next;
    struct s_philo *prev;
    struct s_philo *first;
    struct s_philo *last;
}               t_philo;

typedef struct  s_node
{
    int n_philos;
    int die;
    int eat;
    int slpeep;
    int think;
    int n_eats;
    t_philo *philo;
}               t_node;

void    create_philo(t_node *node, int index);
void    data_common(t_philo *new, t_node *node, int id);
void    *threads(void *philo_current);
void		print_message(t_philo *philo, int i);
void		print_eat(t_philo *philo, int i);
t_boolean	run_philos(t_philo *philo);
t_boolean	end_philos(t_philo *philo);
void    init_node(t_node *node, char **argv);
//

//

#endif