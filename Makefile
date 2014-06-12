#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/05/16 15:00:18 by mle-roy           #+#    #+#              #
#    Updated: 2014/06/12 17:11:30 by mle-roy          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME_Serv = serveur

SRC_S = serveur.c debug.c error_serv.c get_zaap.c init_map.c get_arg.c \
		init_fd.c check_fd.c check_gfx.c gfx_buff.c check_players.c \
		check_tmp.c add_new_player.c player_in_egg.c move_player_map.c \
		init_serv.c

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
