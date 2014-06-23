/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_see.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:15:16 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 15:53:54 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

static void		ft_addinv(char **s, t_stock *inv)
{
	int		bol;

	bol = 0;
	bol = ft_addnstr(s, bol, inv->food, "nourriture");
	bol = ft_addnstr(s, bol, inv->linemate, "linemate");
	bol = ft_addnstr(s, bol, inv->deraumere, "deraumere");
	bol = ft_addnstr(s, bol, inv->sibur, "sibur");
	bol = ft_addnstr(s, bol, inv->mendiane, "mendiane");
	bol = ft_addnstr(s, bol, inv->phiras, "phiras");
	bol = ft_addnstr(s, bol, inv->thystame, "thystame");
}

static char		*spot_player(t_caps *bwscps, int flag)
{
	int			nb;
	char		*ret;

	nb = 0;
	while (bwscps)
	{
		if (bwscps && bwscps->player != NULL)
			nb++;
		bwscps = bwscps->next;
	}
	if (flag == 1)
		nb--;
	if (nb > 0)
	{
		ret = ft_strnew(0);
		ft_addnstr(&ret, 0, nb, "joueur");
		return (ret);
	}
	return (NULL);
}

char			*see_spot(t_map map, int flag)
{
	char		*inv;
	char		*player;
	char		*ret;

	inv = ft_strnew(0);
	ft_addinv(&inv, map.ressources);
	player = spot_player(map.list, flag);
	if (player)
	{
		ret = ft_strjoinwsep(player, inv, ' ');
		free(inv);
		free(player);
	}
	else
		return (inv);
	return (ret);
}

int				make_see(t_action *act, t_player *pl, t_zaap *zaap)
{
	char		ret[BUFF + 1];
	char		*all;

	(void)act;
	if (pl->dir == SOUTH)
		all = see_south(pl->pos_x, pl->pos_y, zaap, pl->lvl);
	else if (pl->dir == NORTH)
		all = see_north(pl->pos_x, pl->pos_y, zaap, pl->lvl);
	else if (pl->dir == EAST)
		all = see_east(pl->pos_x, pl->pos_y, zaap, pl->lvl);
	else if (pl->dir == WEST)
		all = see_west(pl->pos_x, pl->pos_y, zaap, pl->lvl);
	all[(ft_strlen(all) - 2)] = '\0';
	sprintf(ret, "{%s}\n", all);
	free(all);
	add_player_buff(pl, ret);
	return (0);
}
