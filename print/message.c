/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:47:57 by juan-gon          #+#    #+#             */
/*   Updated: 2022/02/28 14:41:39 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "message.h"

void print_message(char *message)
{
    write(1, &message, ft_strlen(message));
}

//timestamp_in_ms X has taken a fork
//timestamp_in_ms X is eating
//timestamp_in_ms X is sleeping
//timestamp_in_ms X is thinking
//timestamp_in_ms X died


