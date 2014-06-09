/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zaap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:50 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/09 22:01:53 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZAAP_H
# define ZAAP_H

# define USAGE1 "Usage: ./serveur -p <port> -x <width> -y <height>"
# define USAGE2 "-n <team> [<team>] [<team>] ... -c <nb> -t <t>\n"

# define AVC 1
# define DRT 2
# define GAU 3
# define SEE 4
# define INV 5
# define TAK 6
# define PUT 7
# define EXP 8
# define BRD 9
# define ELV 10
# define FRK 11
# define CNN 12

# define UP 1
# define RIGHT 2
# define LEFT 3
# define DOWN 4

# define BUFF 1024
# define BUFF_NAME 128

typedef struct			s_action
{
	int					nb;
	time_t				finish;
	int					type;
	char				buff[BUFF];
	struct s_action		*next;
	struct s_action		*prev;
}						t_action;

typedef struct			s_stock
{
	int					food;
	int					linemate;
	int					deraumere;
	int					sibur;
	int					mendiane;
	int					phiras;
	int					thystame;
}						t_stock;

typedef struct			s_player
{
	int					sock;
	int					pos_x;
	int					pos_y;
	int					dir;
	int					lvl;
	int					free; //??
	t_stock				*inventory;
	t_action			*a_first;
	t_action			*a_last;
	char				buff_wr[BUFF];
	struct s_player		*next;
	struct s_player		*prev;
}						t_player;

typedef struct			s_team
{
	char				name[BUFF_NAME];
	int					player_nb;
	t_player			*first;
	struct s_team		*next;
	struct s_team		*prev;
}						t_team;

typedef struct			s_temp
{
	int					sock;
	char				buff_rd[BUFF];
	char				buff_wr[BUFF];
	struct s_temp		*next;
	struct s_temp		*prev;
}						t_temp;

typedef struct			s_caps
{
	t_player			*player;
	struct s_caps		*next;
}						t_caps;

typedef struct			s_map
{
	t_stock				*ressources;
	t_caps				*list;
}						t_map;

typedef struct			s_egg
{
	time_t				hatch;
	char				team[BUFF_NAME];
	struct s_egg		*next;
}						t_egg;

typedef struct			s_zaap
{
	int					sock;
	int					port;
	int					x;
	int					y;
	int					nb_start;
	int					time;
	t_map				***map;
	t_temp				*wait;
	t_team				*teams;
	t_egg				*eggs;
}						t_zaap;

#endif
