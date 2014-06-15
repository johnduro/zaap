/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zaap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:50 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/14 20:24:29 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZAAP_H
# define ZAAP_H

# define USAGE1 "Usage: ./serveur -p <port> -x <width> -y <height>"
# define USAGE2 " -n <team> [<team>] [<team>] ... -c <nb> -t <t>\n"

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
# define EAST 2
# define SOUTH 3
# define WEST 4

# define START_FOOD 10

# define BUFF 1024
# define BUFF_NAME 128

#include <time.h>
#include <sys/select.h>

typedef struct			s_action
{
//	int					nb;
	struct timeval		finish;
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

typedef struct	s_team		t_team;

typedef struct			s_player
{
	int					sock;
	int					pos_x;
	int					pos_y;
	int					dir;
	int					lvl;
	int					nba;
	int					alive;
	struct timeval		tick;
//	int					free; //??
	t_stock				*inventory;
	t_action			*a_first;
	t_action			*a_last;
	t_team				*p_team;
	char				buff_wr[BUFF + 1];
	char				buff_rd[BUFF + 1];
	struct s_player		*next;
	struct s_player		*prev;
}						t_player;

typedef struct			s_egg
{
	int					x;
	int					y;
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

typedef struct			s_buff
{
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
void			remove_pl(t_player *pl, t_team *team, t_zaap *zaap);
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
void			send_new_player(t_player *pl, t_gfx *gfx, t_team *team);
void			send_teams_gfx(t_gfx *gfx, t_zaap *zaap);
void			send_all_map(t_gfx *gfx, t_zaap *zaap);
void			send_time_gfx(t_gfx *gfx, t_zaap *zaap);
void			send_dim_gfx(t_gfx *gfx, t_zaap *zaap);
int         	vd(int coor, int max);
int         	is_time_yet(struct timeval ok);
void        	action_time(struct timeval *res, int time, int lenght);
int				gfx_set_time(char **tab, t_gfx *gfx, t_zaap *zaap);
int				gfx_get_time(char **tab, t_gfx *gfx, t_zaap *zaap);
char        	*get_stock(t_stock *inv);
char        	*pos_n_stock(t_stock *inv, int x, int y);
void        	get_pos_player_gfx(t_player *pl, t_gfx *gfx);
void			send_spot(t_map map, t_gfx *gfx, int y, int x);
void			treat_gfx(t_gfx *gfx, t_zaap *zaap);
int				gfx_teams_name(char **tab, t_gfx *gfx, t_zaap *zaap);
int				gfx_all_map(char **tab, t_gfx *gfx, t_zaap *zaap);
int				gfx_spot_content(char **tab, t_gfx *gfx, t_zaap *zaap);
int				gfx_map_size(char **tab, t_gfx *gfx, t_zaap *zaap);
t_player		*get_player(int sock, t_zaap *zaap);
int				gfx_player_pos(char **tab, t_gfx *gfx, t_zaap *zaap);
int				gfx_player_lvl(char **tab, t_gfx *gfx, t_zaap *zaap);
int				gfx_player_inv(char **tab, t_gfx *gfx, t_zaap *zaap);
char			*get_pos(int x, int y);
char			*get_stock(t_stock *inv);
char			*pos_n_stock(t_stock *inv, int x, int y);
void			send_spot(t_map map, t_gfx *gfx, int y, int x);
char			**split_n_trim(char *str);
void			remove_player_map(t_player *player, t_zaap *zaap);
void			add_player_map(t_player *player, t_zaap *zaap);

#endif
