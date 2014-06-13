/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:28 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/13 20:23:55 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "zaap.h"
#include "libft.h"

int			gfx_set_time(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	(void)tab;
	(void)gfx;
	(void)zaap;
	return (0);
}

int			gfx_get_time(char **tab, t_gfx *gfx, t_zaap *zaap) //ok
{
	(void)tab;
	send_time_gfx(gfx, zaap);
	return (0);
}

int			gfx_player_inv(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	(void)tab;
	(void)gfx;
	(void)zaap;
	return (0);
}

int			gfx_player_lvl(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	(void)tab;
	(void)gfx;
	(void)zaap;
	return (0);
}

int			gfx_player_pos(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	(void)tab;
	(void)gfx;
	(void)zaap;
	return (0);
}

int			gfx_teams_name(char **tab, t_gfx *gfx, t_zaap *zaap) //ok
{
	(void)tab;
	send_teams_gfx(gfx, zaap);
	return (0);
}

int			gfx_all_map(char **tab, t_gfx *gfx, t_zaap *zaap) //ok
{
	(void)tab;
	send_all_map(gfx, zaap);
	return (0);
}

int			gfx_spot_content(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	(void)tab;
	(void)gfx;
	(void)zaap;
	return (0);
}

int			gfx_map_size(char **tab, t_gfx *gfx, t_zaap *zaap) //ok
{
	(void)tab;
	send_dim_gfx(gfx, zaap);
	return (0);
}

t_pgfx		*get_parse_gfx(void)
{
	static t_pgfx	parse[] =

	{
	{"msz", &gfx_map_size},
	{"bct", &gfx_spot_content},
	{"mct", &gfx_all_map},
	{"tna", &gfx_teams_name},
	{"ppo", &gfx_player_pos},
	{"plv", &gfx_player_lvl},
	{"pin", &gfx_player_inv},
	{"sgt", &gfx_get_time},
	{"sst", &gfx_set_time},
	{NULL, NULL}
	};
	return (parse);
}

void	treat_gfx(t_gfx *gfx, t_zaap *zaap)
{
	char		*trim;
	char		**split;
	t_pgfx		*parse;
	int			i;

	trim = ft_strtrim(gfx->buff_rd);
	split = ft_strsplit(trim, ' ');
	parse = get_parse_gfx();
	i = 0;
	while (parse[i].name)
	{
		if (!ft_strcmp(parse[i].name, *split))
		{
			parse[i].fn(split, gfx, zaap);
			break ;
		}
		i++;
	}
	ft_strclr(gfx->buff_rd);
	free(trim);
	ft_tabfree(&split);
}

void	treat_player(t_player *player, t_zaap *zaap)
{
	(void)zaap;
	ft_strclr(player->buff_rd);//FAKE
	ft_strcat(player->buff_wr, "CMD OK\n"); //FAKE
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
