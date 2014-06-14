/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:48:51 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/14 19:31:22 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

/*
t_caps		*init_caps(t_player *player, t_egg *egg)
{
	t_caps		*new;

	if ((new = (t_caps *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->player = NULL;
	new->egg = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (player)
		new->player = player;
	else if (egg)
		new->egg = egg;
	return (new);
}
*/
/*
void		send_time_gfx(t_gfx *gfx, t_zaap *zaap)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(zaap->time);
	tmp2 = ft_strjoin("sgt ", tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, "\n");
	free(tmp2);
	add_to_gfx_buf(gfx, tmp);
	free(tmp);
}
*/
/*
char		*get_pos(int x, int y)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_itoa(x);
	tmp2 = ft_itoa(y);
	tmp3 = ft_strjoinwsep(tmp, tmp2, ' ');
	free(tmp);
	free(tmp2);
	return (tmp3);
}
*/
/*
void		send_dim_gfx(t_gfx *gfx, t_zaap *zaap)
{
	char	*tmp;
	char	*tmp2;

	tmp = get_pos(zaap->x, zaap->y);
	tmp2 = ft_strjoin("msz ", tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, "\n");
	free(tmp2);
	add_to_gfx_buf(gfx, tmp);
	free(tmp);
}
*/
/*
static char		*get_ressources(t_stock *inv, int i)
{
	if (i == 0)
		return (ft_itoa(inv->food));
	else if (i == 1)
		return (ft_itoa(inv->linemate));
	else if (i == 2)
		return (ft_itoa(inv->deraumere));
	else if (i == 3)
		return (ft_itoa(inv->sibur));
	else if (i == 4)
		return (ft_itoa(inv->mendiane));
	else if (i == 5)
		return (ft_itoa(inv->phiras));
	else if (i == 6)
		return (ft_itoa(inv->thystame));
	return (NULL);
}

char		*get_stock(t_stock *inv)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*keep;

	i = 1;
	tmp = get_ressources(inv, 0);
	while (i < 7)
	{
		tmp2 = get_ressources(inv, i);
		keep = tmp;
		tmp = ft_strjoinwsep(tmp, tmp2, ' ');
		free(keep);
		free(tmp2);
		i++;
	}
	return (tmp);
}

char		*pos_n_stock(t_stock *inv, int x, int y)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = get_pos(x, y);
	tmp2 = get_stock(inv);
	tmp3 = ft_strjoinwsep(tmp, tmp2, ' ');
	free(tmp);
	free(tmp2);
	return (tmp3);
}

void		send_spot(t_map map, t_gfx *gfx, int y, int x)
{
	char	ret[BUFF + 1];
	char	*tmp;

	ft_strcpy(ret, "bct ");
	tmp = pos_n_stock(map.ressources, x, y);
	ft_strcat(ret, tmp);
	free(tmp);
	ft_strcat(ret, "\n");
	add_to_gfx_buf(gfx, ret);
}
*/

void		send_teams_gfx(t_gfx *gfx, t_zaap *zaap)
{
	t_team		*bwst;
	char		*tmp;
	char		*to_send;

	bwst = zaap->teams;
	while (bwst)
	{
		tmp = ft_strjoin("tna ", bwst->name);
		to_send = ft_strjoin(tmp, "\n");
		free(tmp);
		add_to_gfx_buf(gfx, to_send);
		free(to_send);
		bwst = bwst->next;
	}
}

/*
char		*pos_n_dir(t_player *pl)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = get_pos(pl->pos_x, pl->pos_y);
	tmp2 = ft_itoa(pl->dir);
	tmp3 = ft_strjoinwsep(tmp, tmp2, ' ');
	free(tmp);
	free(tmp2);
	return (tmp3);
}

void		get_pos_player_gfx(t_player *pl, t_gfx *gfx)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_itoa(pl->sock);
	tmp2 = ft_strjoin("ppo #", tmp);
	free(tmp);
	tmp3 = pos_n_dir(pl);
	tmp = ft_strjoinwsep(tmp2, tmp3, ' ');
	free(tmp2);
	free(tmp3);
	tmp2 = ft_strjoin(tmp, "\n");
	free(tmp);
	add_to_gfx_buf(gfx, tmp2);
	free(tmp2);
}

static char		*new_player_gfx(t_player *pl)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_itoa(pl->sock);
	tmp2 = ft_strjoin("pnw #", tmp);
	free(tmp);
	tmp3 = get_pos(pl->pos_x, pl->pos_y);
	tmp = ft_strjoinwsep(tmp2, tmp3, ' ');
	free(tmp2);
	free(tmp3);
	tmp2 = ft_itoa(pl->dir);
	tmp3 = ft_strjoinwsep(tmp, tmp2, ' ');
	free(tmp);
	free(tmp2);
	return (tmp3);
}

void		send_new_player(t_player *pl, t_gfx *gfx, t_team *team)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = new_player_gfx(pl);
	tmp2 = ft_itoa(pl->lvl);
	tmp3 = ft_strjoinwsep(tmp, tmp2, ' ');
	free(tmp);
	free(tmp2);
	tmp = ft_strjoinwsep(tmp3, team->name, ' ');
	free(tmp3);
	tmp2 = ft_strjoin(tmp, "\n");
	free(tmp);
	add_to_gfx_buf(gfx, tmp2);
	free(tmp2);
}
*/
static void			send_all_players(t_gfx *gfx, t_zaap *zaap)
{
	t_team		*bwst;
	t_player	*bwspl;

	bwst = zaap->teams;
	while (bwst)
	{
		if (bwst->first)
		{
			bwspl = bwst->first;
			while (bwspl)
			{
				send_new_player(bwspl, gfx, bwst);
				bwspl = bwspl->next;
			}
		}
		bwst = bwst->next;
	}
}

void				send_all_map(t_gfx *gfx, t_zaap *zaap)
{
	int		i;
	int		j;

	i = 0;
	while (i < zaap->y)
	{
		j = 0;
		while (j < zaap->x)
		{
			send_spot(zaap->map[i][j], gfx, i, j);
			j++;
		}
		i++;
	}
}

static void			first_map_send(t_gfx *gfx, t_zaap *zaap)
{
	send_dim_gfx(gfx, zaap);
	send_time_gfx(gfx, zaap);
	send_all_map(gfx, zaap);
	send_teams_gfx(gfx, zaap);
	send_all_players(gfx, zaap);
}

t_gfx				*init_gfx(int sock, t_zaap *zaap)
{
	t_gfx		*new;

	if ((new = (t_gfx *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->sock = sock;
	new->to_send = 0;
	new->list = NULL;
	first_map_send(new, zaap);
	return (new);
}
