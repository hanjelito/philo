# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juan-gon <juan-gon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/13 14:11:23 by juan-gon          #+#    #+#              #
#    Updated: 2022/03/13 14:11:24 by juan-gon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

COMP = gcc

COMP_FLAGS = -g -Wall -Wextra -Werror 


SRCS = 	philosophers/philosophers.c \
		philosophers/create_philos.c \
		philosophers/threads.c \
		philosophers/create_threads.c \
		utils/ft_atoi.c \
		time/time.c \
		main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(COMP) $(COMP_FLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	@$(COMP) $(COMP_FLAGS) -c $< -o $@

leaks:
	valgrind --leak-check=yes ./$(NAME)no

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all leaks clean fclean re