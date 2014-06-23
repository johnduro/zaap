/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_take_drop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:07:30 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 21:37:12 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

int				change_linemate(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->linemate <= 0)
			return (-1);
		(map->linemate)--;
		(inv->linemate)++;
	}
	else
	{
		if (inv->linemate <= 0)
			return (-1);
		(map->linemate)++;
		(inv->linemate)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, LIN);
	return (0);
}

static int		change_food(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->food <= 0)
			return (-1);
		(map->food)--;
		(inv->food)++;
	}
	else
	{
		if (inv->food <= 0)
			return (-1);
		(map->food)++;
		(inv->food)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, FOD);
	return (0);
}

static int		obj_use(char *str, t_player *pl, t_zaap *zaap, char flag)
{
	if (!ft_strncmp(str, "nourriture", 10))
		return (change_food(pl, zaap, flag));
	else if (!ft_strncmp(str, "linemate", 8))
		return (change_linemate(pl, zaap, flag));
	else if (!ft_strncmp(str, "deraumere", 9))
		return (change_deraumere(pl, zaap, flag));
	else if (!ft_strncmp(str, "sibur", 5))
		return (change_sibur(pl, zaap, flag));
	else if (!ft_strncmp(str, "mendiane", 8))
		return (change_mendiane(pl, zaap, flag));
	else if (!ft_strncmp(str, "phiras", 6))
		return (change_phiras(pl, zaap, flag));
	else if (!ft_strncmp(str, "thystame", 8))
		return (change_thystame(pl, zaap, flag));
	return (-1);
}

int				make_drop(t_action *act, t_player *pl, t_zaap *zaap)
{
	int		ret;
	char	*tmp;
	t_map	map;

	ret = -1;
	ret = obj_use(act->buff, pl, zaap, 0);
	if (ret)
		add_player_buff(pl, "ko\n");
	else
		add_player_buff(pl, "ok\n");
	if (zaap->gfx)
	{
		tmp = get_inv_gfx(pl->sock, zaap);
		add_to_gfx_buf(zaap->gfx, tmp);
		free(tmp);
		map = zaap->map[pl->pos_y][pl->pos_x];
		send_spot(map, zaap->gfx, pl->pos_y, pl->pos_x);
	}
	return (0);
}

int				make_take(t_action *act, t_player *pl, t_zaap *zaap)
{
	int		ret;
	char	*tmp;
	t_map	map;

	ret = -1;
	ret = obj_use(act->buff, pl, zaap, 1);
	if (ret)
		add_player_buff(pl, "ko\n");
	else
		add_player_buff(pl, "ok\n");
	if (zaap->gfx)
	{
		tmp = get_inv_gfx(pl->sock, zaap);
		add_to_gfx_buf(zaap->gfx, tmp);
		free(tmp);
		map = zaap->map[pl->pos_y][pl->pos_x];
		send_spot(map, zaap->gfx, pl->pos_y, pl->pos_x);
	}
	return (0);
}
