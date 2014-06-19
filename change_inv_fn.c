/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_inv_fn.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:11:11 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/19 18:22:28 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"
#include "libft.h"

int			change_thystame(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->thystame <= 0)
			return (-1);
		(map->thystame)--;
		(inv->thystame)++;
	}
	else
	{
		if (inv->thystame <= 0)
			return (-1);
		(map->thystame)++;
		(inv->thystame)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, THY);
	return (0);
}

int			change_phiras(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->phiras <= 0)
			return (-1);
		(map->phiras)--;
		(inv->phiras)++;
	}
	else
	{
		if (inv->phiras <= 0)
			return (-1);
		(map->phiras)++;
		(inv->phiras)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, PHY);
	return (0);
}

int			change_mendiane(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->mendiane <= 0)
			return (-1);
		(map->mendiane)--;
		(inv->mendiane)++;
	}
	else
	{
		if (inv->mendiane <= 0)
			return (-1);
		(map->mendiane)++;
		(inv->mendiane)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, MEN);
	return (0);
}

int			change_sibur(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->sibur <= 0)
			return (-1);
		(map->sibur)--;
		(inv->sibur)++;
	}
	else
	{
		if (inv->sibur <= 0)
			return (-1);
		(map->sibur)++;
		(inv->sibur)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, SIR);
	return (0);
}

int			change_deraumere(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->deraumere <= 0)
			return (-1);
		(map->deraumere)--;
		(inv->deraumere)++;
	}
	else
	{
		if (inv->deraumere <= 0)
			return (-1);
		(map->deraumere)++;
		(inv->deraumere)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, DER);
	return (0);
}
