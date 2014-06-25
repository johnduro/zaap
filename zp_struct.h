/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zp_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 18:35:35 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/25 18:56:14 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZP_STRUCT_H
# define ZP_STRUCT_H

typedef struct			s_action
{
	struct timeval		finish;
	int					type;
	int					lenght;
	char				buff[BUFF + 1];
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

typedef struct s_team	t_team;

typedef struct			s_buff
{
	char				*buff_wr;
	struct s_buff		*next;
}						t_buff;

typedef struct			s_player
{
	int					sock;
	int					pos_x;
	int					pos_y;
	int					dir;
	int					lvl;
	int					nba;
	int					alive;
	int					to_send;
	struct timeval		tick;
	t_stock				*inventory;
	t_action			*a_first;
	t_action			*a_last;
	t_team				*p_team;
	t_buff				*list;
	char				buff_rd[BUFF + 1];
	struct s_player		*next;
	struct s_player		*prev;
}						t_player;

typedef struct			s_egg
{
	int					x;
	int					y;
	int					ok;
	int					nb;
	struct timeval		hatch;
	struct s_egg		*next;
	struct s_egg		*prev;
}						t_egg;

struct					s_team
{
	char				name[BUFF_NAME + 1];
	int					player_nb;
	int					places;
	t_player			*first;
	t_egg				*eggs;
	struct s_team		*next;
	struct s_team		*prev;
};

typedef struct			s_temp
{
	int					sock;
	char				buff_rd[BUFF + 1];
	char				buff_wr[BUFF + 1];
	struct s_temp		*next;
	struct s_temp		*prev;
}						t_temp;

typedef struct			s_caps
{
	t_player			*player;
	t_egg				*egg;
	struct s_caps		*next;
	struct s_caps		*prev;
}						t_caps;

typedef struct			s_map
{
	t_stock				*ressources;
	t_caps				*list;
}						t_map;

typedef struct			s_gfx
{
	int					sock;
	char				buff_rd[BUFF + 1];
	int					to_send;
	t_buff				*list;
}						t_gfx;

typedef struct			s_inc
{
	struct timeval		ref;
	int					check;
	int					nb;
	struct s_inc		*next;
	struct s_inc		*prev;
}						t_inc;

typedef struct			s_zaap
{
	int					sock;
	int					x;
	int					y;
	int					max;
	int					nb_start;
	int					time;
	fd_set				fd_rd;
	fd_set				fd_wr;
	t_map				**map;
	t_temp				*wait;
	t_team				*teams;
	t_inc				*inc;
	t_gfx				*gfx;
	struct timeval		regen;
}						t_zaap;

typedef struct			s_fill
{
	int					x;
	int					y;
	int					min;
	int					max;
}						t_fill;

typedef int		(*t_fn)(char **, t_gfx *, t_zaap *);

typedef struct			s_prs
{
	char				*name;
	t_fn				fn;
}						t_prs;

typedef int		(*t_fn2)(char **, t_player *, t_zaap *);

typedef struct			s_ply
{
	char				*name;
	t_fn2				fn;
}						t_ply;

typedef int		(*t_fn3)(t_action *, t_player *, t_zaap *);

typedef struct			s_pac
{
	int					type;
	t_fn3				fn;
}						t_pac;

#endif
