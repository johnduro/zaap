/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:28 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/14 20:37:29 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "zaap.h"
#include "libft.h"

int			vd(int coor, int max)
{
	if (coor >= 0 && coor < max)
		return (coor);
	else if (coor < 0)
	{
		while (coor < 0)
			coor += max;
		return (coor);
	}
	else if (coor >= max)
	{
		while (coor >= max)
			coor -= max;
		return (coor);
	}
	return (0);
}

char	**split_n_trim(char *str)
{
	char	**tab;
	char	*trim;

	trim = ft_strtrim(str);
	tab = ft_strsplit(trim, ' ');
	free(trim);
	return (tab);
}

t_action	*init_action(int type, char *str, int lenght, t_zaap *zaap)
{
	t_action	*new;

	if ((new = (t_action *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2); //verifier
	new->type = type;
	if (str && *str != '\0')
		ft_strcat(new->buff, str);
	action_time(&(new->finish), zaap->time, lenght);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		add_action_player(t_action *action, t_player *player)
{
	(player->nba)++;
	if (player->a_first == NULL)
	{
		player->a_first = action;
		player->a_last = action;
	}
	else
	{
		player->a_last->next = action;
		action->prev = player->a_last;
		player->a_last = action;
	}
}

int		player_connect(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(CNN, tab[1], 0, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_fork(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(FRK, tab[1], 42, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_incant(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(ELV, tab[1], 300, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_broadcast(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(BRD, tab[1], 7, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_expulse(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(EXP, tab[1], 7, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_drop(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(PUT, tab[1], 7, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_take(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(TAK, tab[1], 7, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_inv(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(INV, tab[1], 1, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_see(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(SEE, tab[1], 7, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_left(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(GAU, tab[1], 7, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_right(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(DRT, tab[1], 7, zaap);
	add_action_player(action, pl);
	return (0);
}

int		player_go(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(AVC, tab[1], 7, zaap);
	add_action_player(action, pl);
	return (0);
}

t_ply	*get_parse_play(void)
{
	static t_ply	parse[] =

	{
		{"avance", &player_go},
		{"droite", &player_right},
		{"gauche", &player_left},
		{"voir", &player_see},
		{"inventaire", &player_inv},
		{"prend", &player_take},
		{"pose", &player_drop},
		{"expulse", &player_expulse},
		{"broadcast", &player_broadcast},
		{"incantation", &player_incant},
		{"fork", &player_fork},
		{"connect_nbr", &player_connect},
		{NULL, NULL}
	};
	return (parse);
}

void	treat_player(t_player *pl, t_zaap *zaap)
{
	char	**split;
	t_ply	*parse;
	int		i;
	int		ret; //besoin ?

	i = 0;
	ret = 1;
	split = split_n_trim(pl->buff_rd);
	parse = get_parse_play();
	while (parse[i].name)
	{
		if (!ft_strcmp(parse[i].name, *split))
		{
			ret = parse[i].fn(split, pl, zaap);
			break ;
		}
		i++;
	}
	(void)ret;
//	check_player_ret(ret, pl);
	ft_strclr(pl->buff_rd);
	ft_tabfree(&split);
}
//int is_time_yet(struct timeval ok);
//void action_time(struct timeval *res, int time, int lenght);

void	add_player_buff(t_player *pl, char *str)
{
	if ((BUFF - (ft_strlen(pl->buff_wr) + ft_strlen(str))) > 1)
		ft_strcat(pl->buff_wr, str);
}

int		check_food(t_player *pl, t_zaap *zaap)
{
	if (is_time_yet(pl->tick))
	{
		(pl->inventory->food)--;
		if (pl->inventory->food <= 0)
		{
			pl->alive = 0;
			add_player_buff(pl, "mort\n");
			return (-1);
		}
		else
			action_time(&(pl->tick), zaap->time, 126);
	}
	return (0);
}

int		make_connect(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_fork(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_incant(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_broadcast(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_expulse(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_drop(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_take(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_inv(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_see(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_left(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_right(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

int		make_go(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	(void)pl;
	(void)zaap;
	return (0);
}

t_pac	*get_parse_make(void)
{
	static t_pac	parse[] =

	{
	{AVC, &make_go},
	{DRT, &make_right},
	{GAU, &make_left},
	{SEE, &make_see},
	{INV, &make_inv},
	{TAK, &make_take},
	{PUT, &make_drop},
	{EXP, &make_expulse},
	{BRD, &make_broadcast},
	{ELV, &make_incant},
	{FRK, &make_fork},
	{CNN, &make_connect},
	{0, NULL}
	};
	return (parse);
}

void	make_action(t_action *act, t_player *pl, t_zaap *zaap)
{
	int		i;
	t_pac	*parse;

	i = 0;
	parse = get_parse_make();
	while (i < 12)
	{
		if (parse[i].type == act->type)
			parse[i].fn(act, pl, zaap);
		i++;
	}
	if (act->next == NULL)
	{
		pl->a_first = NULL;
		pl->a_last = NULL;
	}
	else if (act->next)
	{
		pl->a_first = act->next;
		pl->a_first->prev = NULL;
	}
	free(act);
}

void	player_game(t_player *pl, t_zaap *zaap)
{
	if (check_food(pl, zaap))
		return ;
	if (pl->a_first)
	{
		if (is_time_yet(pl->a_first->finish))
			make_action(pl->a_first, pl, zaap);
	}
}

void	make_game(t_zaap *zaap)
{
	t_team		*bwst;
	t_player	*bwspl;

	bwst = zaap->teams;
	while (bwst)
	{
//		check_eggs(bwst, zaap);//a faire
		bwspl = bwst->first;
		while (bwspl)
		{
			player_game(bwspl, zaap);
			bwspl = bwspl->next;
		}
		bwst = bwst->next;
	}
}

void	loop_map(t_zaap *zaap)
{
	int					ret;
	struct timeval		tv;

	while (42)
	{
		ret = 0;
		make_game(zaap); //a faire
		init_fd(zaap);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		ret = select(zaap->max + 1, &zaap->fd_rd, &zaap->fd_wr, NULL, &tv);
		check_fd(ret, zaap);
	}
}

int		main(int argc, char **argv)
{
	t_zaap		*zaap;

	if (argc < 12)
		zaap_error(-1);
	zaap = get_zaap(argv);
	debug_1(zaap);
	loop_map(zaap);
//	exit_zaapy(zaap);
	return (0);
}
