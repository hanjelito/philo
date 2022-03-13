/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:09:09 by juan-gon          #+#    #+#             */
/*   Updated: 2022/03/13 14:30:54 by juan-gon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_TIME_H
# define GET_TIME_H

# include "../utils/libft.h"
# include "../philosophers/philosophers.h"

unsigned long	t_get_ms(void);
void			ft_leep_ms(unsigned int milliseconds);
long			t_diff_ms(unsigned long time1, unsigned long time2);

#endif
