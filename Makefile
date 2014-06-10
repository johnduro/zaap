#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/16 15:00:18 by mle-roy           #+#    #+#              #
#    Updated: 2014/05/21 14:11:38 by mle-roy          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME_Serv = serveur

SRC_S = serveur.c

OBJ_S = $(SRC_S:.c=.o)


FLAGS = -g3 -Wall -Wextra -Werror

all: build $(NAME_Serv) finish

build:
	@make -C libft

$(NAME_Serv): $(OBJ_S)
	@gcc $(OBJ_S) -L libft -lft -o $(NAME_Serv)


%.o: %.c
	@gcc $(FLAGS) -c -I libft/includes $<

clean:
	@rm -f $(OBJ_S)
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME_Serv)
	@make -C libft/ fclean

re: fclean all

finish:
	@(echo "[\033[32m$(NAME_Serv)\033[00m]")

.PHONY: all build clean fclean re
