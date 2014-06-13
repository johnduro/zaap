/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zaap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:50 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/13 17:07:03 by mle-roy          ###   ########.fr       */
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

# define NORTH 1
# define EST 2
# define SOUTH 3
# define WEST 4

# define START_FOOD 10

# define BUFF 1024
# define BUFF_NAME 128

#include <time.h>
#include <sys/select.h>

typedef struct			s_action
{
	int					nb;
	time_t				finish;
	int					type;
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
	char				buff_wr[BUFF + 1];
	char				buff_rd[BUFF + 1];
	struct s_player		*next;
	struct s_player		*prev;
}						t_player;

typedef struct			s_egg
{
	int					x;
	int					y;
	time_t				hatch;
//	char				team[BUFF_NAME];//besoin ??
	struct s_egg		*next;
	struct s_egg		*prev;
}						t_egg;

typedef struct			s_team
{
	char				name[BUFF_NAME + 1];
	int					player_nb;
	int					places;
	t_player			*first;
	t_egg				*eggs;
	struct s_team		*next;
	struct s_team		*prev;
}						t_team;

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

typedef struct			s_buff
{
//	char				buff_wr[BUFF + 1];
	char				*buff_wr;
	struct s_buff		*next;
}						t_buff;

typedef struct			s_gfx
{
	int					sock;
	char				buff_rd[BUFF + 1];
	int					to_send;
	t_buff				*list;
}						t_gfx;

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
	t_gfx				*gfx;
}						t_zaap;

/*
** DEBUG
*/

void    debug_1(t_zaap *zaap);

/*
** ERROR
*/

int zaap_error(int code);



t_zaap          *get_zaap(char **arg);
t_stock         *get_inv(void);
int             rand_a_b(int a, int b);
void    		get_map(t_zaap *zaap);
int             get_arg(t_zaap *zaap, char **arg);
void			init_fd(t_zaap *zaap);
void			check_fd(int ret, t_zaap *zaap);
int				find_read(char *str);
void			check_gfx(t_zaap *zaap, t_gfx *gfx);
void			treat_gfx(t_gfx *gfx, t_zaap *zaap);
void			add_to_gfx_buf(t_gfx *gfx, char *str);
void			check_players_fd(t_player *bwspl, t_zaap *zaap, t_team *team);
void			treat_player(t_player *player, t_zaap *zaap);
void			remove_pl(t_player *pl, t_team *team);
void			check_tmp_fd(t_temp *bwstmp, t_zaap *zaap);
void			remove_tmp(t_temp *tmp, t_zaap *zaap, int flag);
void			add_new_client(t_team *team, int sock, t_zaap *zaap);
t_team			*check_teams(char *str, t_team *bwst);
t_gfx			*init_gfx(int sock, t_zaap *zaap);
t_caps			*init_caps(t_player *player, t_egg *egg);
void			place_player_in_egg(t_team *t, t_player *n, t_egg *e, t_zaap *z);
t_egg			*egg_rdy(t_egg *bwsegg);
void			remove_egg_map(t_egg *egg, t_zaap *zaap);
void			add_player_to_map(t_player *player, t_zaap *zaap);

#endif
