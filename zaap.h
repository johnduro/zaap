/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zaap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:50 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 19:14:55 by mle-roy          ###   ########.fr       */
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

# define FOD 0
# define LIN 1
# define DER 2
# define SIR 3
# define MEN 4
# define PHY 5
# define THY 6

# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

# define START_FOOD 10

# define BUFF 8024
# define BUFF_NAME 128

# define MIN_X 17
# define MIN_Y 17

# define INV_1 "{nourriture %d, linemate %d, deraumere %d, sibur %d,"
# define INV_2 " mendiane %d, phiras %d, thystame %d}\n"

#include <time.h>
#include <sys/select.h>

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

typedef struct	s_team		t_team;

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
void			treat_player(t_player *pl, t_zaap *zaap);
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
void			add_action_player(t_action *act, t_player *pl, t_zaap *zp);
t_action		*init_action(int type, char *str, int lenght);
int				player_go(char **tab, t_player *pl, t_zaap *zaap);
int				player_see(char **tab, t_player *pl, t_zaap *zaap);
int				player_left(char **tab, t_player *pl, t_zaap *zaap);
int				player_right(char **tab, t_player *pl, t_zaap *zaap);
int				player_inv(char **tab, t_player *pl, t_zaap *zaap);
int				player_broadcast(char **tab, t_player *pl, t_zaap *zaap);
int				player_expulse(char **tab, t_player *pl, t_zaap *zaap);
int				player_drop(char **tab, t_player *pl, t_zaap *zaap);
int				player_take(char **tab, t_player *pl, t_zaap *zaap);
int				player_connect(char **tab, t_player *pl, t_zaap *zaap);
int				player_fork(char **tab, t_player *pl, t_zaap *zaap);
int				player_incant(char **tab, t_player *pl, t_zaap *zaap);
void			add_caps_map(t_caps *caps, int x, int y, t_zaap *zaap);
void			send_hatching_gfx(int sock, t_gfx *gfx);
void			remove_egg_team(t_egg *egg, t_team *team);
void			start_elev(t_action *act, t_player *pl, t_zaap *zaap);
void			prep_next_act(t_action *act, t_player *pl, t_zaap *zaap);
void			check_eggs(t_team *team, t_zaap *zaap);
void			player_game(t_player *pl, t_zaap *zaap);
void			prep_next_act(t_action *act, t_player *pl, t_zaap *zaap);
void			start_elev(t_action *act, t_player *pl, t_zaap *zaap);
int				check_lvl_elev(t_caps *bwscps, int lvl, int nb);
int				check_lvl1(t_player *pl, t_zaap *zp);
int				check_lvl2(t_player *pl, t_zaap *zp);
int				check_lvl3(t_player *pl, t_zaap *zp);
int				check_lvl4(t_player *pl, t_zaap *zp);
int				check_lvl5(t_player *pl, t_zaap *zp);
int				check_lvl6(t_player *pl, t_zaap *zp);
int				check_lvl7(t_player *pl, t_zaap *zp);
void			send_failed_elv_gfx(t_player *pl, t_gfx *gfx);
int				make_go(t_action *act, t_player *pl, t_zaap *zaap);
int				make_right(t_action *act, t_player *pl, t_zaap *zaap);
int				make_left(t_action *act, t_player *pl, t_zaap *zaap);
void			move_player(t_player *pl, t_zaap *zaap, int dir);
int				make_take(t_action *act, t_player *pl, t_zaap *zaap);
int				make_drop(t_action *act, t_player *pl, t_zaap *zaap);
int				change_thystame(t_player *pl, t_zaap *zaap, char flag);
int				change_phiras(t_player *pl, t_zaap *zaap, char flag);
int				change_mendiane(t_player *pl, t_zaap *zaap, char flag);
int				change_sibur(t_player *pl, t_zaap *zaap, char flag);
int				change_deraumere(t_player *pl, t_zaap *zaap, char flag);
int				change_linemate(t_player *pl, t_zaap *zaap, char flag);
int				make_see(t_action *act, t_player *pl, t_zaap *zaap);
int				ft_addnstr(char **s, int bol, int n, char *str);
void			ft_strjoin_free(char **s1, char *s2);
char			*see_spot(t_map map, int flag);
char			*see_north(int x, int y, t_zaap *z, int lvl);
char			*see_south(int x, int y, t_zaap *z, int lvl);
char			*see_east(int x, int y, t_zaap *z, int lvl);
char			*see_west(int x, int y, t_zaap *z, int lvl);
int				make_expulse(t_action *act, t_player *pl, t_zaap *zaap);
int				make_incant(t_action *act, t_player *pl, t_zaap *zaap);
int				make_fork(t_action *act, t_player *pl, t_zaap *zaap);
int				make_inv(t_action *act, t_player *pl, t_zaap *zaap);
int				make_connect(t_action *act, t_player *pl, t_zaap *zaap);
int				make_broadcast(t_action *act, t_player *pl, t_zaap *zaap);
void			send_change(int sock, t_gfx *gfx, char flag, int obj);
int				ft_broadcast(t_zaap *zaap, t_player *src, t_player *dest);
void			add_player_buff(t_player *pl, char *str);
int				check_elev(t_player *pl, t_zaap *zaap);
char			*get_inv_gfx(int player, t_zaap *zaap);
char			*get_lvl_gfx(int sock, t_zaap *zaap);
t_buff			*init_buff(void);

#endif
