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

int		player_connect(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}
int		player_fork(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}
int		player_incant(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}
int		player_broadcast(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}
int		player_expulse(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}
int		player_drop(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}
int		player_take(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}

int		player_inv(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}

int		player_see(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}

int		player_left(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}

int		player_right(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
	return (0);
}

int		player_go(char **tab, t_player *pl, t_zaap *zaap)
{
	(void)tab;
	(void)pl;
	(void)zaap;
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
	int		ret;

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

void	loop_map(t_zaap *zaap)
{
	int					ret;
	struct timeval		tv;

	while (42)
	{
		ret = 0;
//		check_actions(zaap); //a faire
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
