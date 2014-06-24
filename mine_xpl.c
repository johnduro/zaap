/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mine_xpl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:16:44 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:19:57 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"
#include "libft.h"

static int		get_nb_team(t_team *bwst)
{
	int		count;

	count = 0;
	while (bwst)
	{
		count++;
		bwst = bwst->next;
	}
	return (count);
}

void			add_res(t_stock *inv, int nb, int type)
{
	if (type == LIN)
		inv->linemate += nb;
	else if (type == DER)
		inv->deraumere += nb;
	else if (type == SIR)
		inv->sibur += nb;
	else if (type == MEN)
		inv->mendiane += nb;
	else if (type == PHY)
		inv->phiras += nb;
	else if (type == THY)
		inv->thystame += nb;
}

static void		xplosion(t_fill f, t_zaap *zp, int type)
{
	int		mod;

	mod = 1;
	add_res(zp->map[f.y][f.x].ressources, rand_a_b(f.min, f.max), type);
	while (mod <= 7)
	{
		line_ns(f, mod, zp, type);
		line_ew(f, mod, zp, type);
		line_sn(f, mod, zp, type);
		line_we(f, mod, zp, type);
		if (f.min)
			f.min--;
		if (f.max > 2)
			f.max--;
		mod++;
	}
}

static void		mine_xplode(t_zaap *zp)
{
	int			type;
	t_fill		fill;

	fill.min = 5;
	fill.max = 10;
	type = 1;
	while (type < 7)
	{
		fill.x = rand_a_b(0, zp->x);
		fill.y = rand_a_b(0, zp->y);
		xplosion(fill, zp, type);
		if (fill.min)
			fill.min--;
		if (fill.max > 5)
			fill.max--;
		type++;
	}
}

void			fill_map(t_zaap *zp)
{
	int		nbtm;

	nbtm = 0;
	nbtm = get_nb_team(zp->teams);
	while (nbtm)
	{
		mine_xplode(zp);
		nbtm--;
	}
}
