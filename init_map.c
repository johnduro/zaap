/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:10:21 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 16:06:07 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

t_caps				*init_caps(t_player *player, t_egg *egg)
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

static t_stock		*gen_ressources(void)
{
	t_stock		*inv;

	inv = get_inv();
	inv->food = rand_a_b(1, 11);
/*	inv->linemate = rand_a_b(0, 11);
	inv->deraumere = rand_a_b(0, 10);
	inv->sibur = rand_a_b(0, 9);
	inv->mendiane = rand_a_b(0, 5);
	inv->phiras = rand_a_b(0, 4);
	inv->thystame = rand_a_b(0, 3);*/
	return (inv);
}

static void			init_map(t_zaap *zaap)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	srandom(time(NULL));
	while (i < zaap->y)
	{
		j = 0;
		while (j < zaap->x)
		{
			zaap->map[i][j].ressources = gen_ressources();
			zaap->map[i][j].list = NULL;
			j++;
		}
		i++;
	}
}

int					get_nb_team(t_team *bwst)
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

void				add_res(t_stock *inv, int nb, int type)
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

typedef struct		s_fill
{
	int				x;
	int				y;
	int				min;
	int				max;
}					t_fill;

void				line_ns(t_fill f, int mod, t_zaap *zp, int type)
{
	int		nb;

	nb = mod * 2;
	f.x = vd(f.x + mod, zp->x);
	f.y = vd(f.y - mod, zp->y);
	while (nb)
	{
		add_res(zp->map[f.y][f.x].ressources, rand_a_b(f.min, f.max), type);
		f.y = vd(f.y + 1, zp->y);
		nb--;
	}
}

void				line_ew(t_fill f, int mod, t_zaap *zp, int type)
{
	int		nb;

	nb = mod * 2;
	f.x = vd(f.x + mod, zp->x);
	f.y = vd(f.y + mod, zp->y);
	while (nb)
	{
		add_res(zp->map[f.y][f.x].ressources, rand_a_b(f.min, f.max), type);
		f.x = vd(f.x - 1, zp->x);
		nb--;
	}
}

void				line_sn(t_fill f, int mod, t_zaap *zp, int type)
{
	int		nb;

	nb = mod * 2;
	f.x = vd(f.x - mod, zp->x);
	f.y = vd(f.y + mod, zp->y);
	while (nb)
	{
		add_res(zp->map[f.y][f.x].ressources, rand_a_b(f.min, f.max), type);
		f.y = vd(f.y - 1, zp->y);
		nb--;
	}
}

void				line_we(t_fill f, int mod, t_zaap *zp, int type)
{
	int		nb;

	nb = mod * 2;
	f.x = vd(f.x - mod, zp->x);
	f.y = vd(f.y - mod, zp->y);
	while (nb)
	{
		add_res(zp->map[f.y][f.x].ressources, rand_a_b(f.min, f.max), type);
		f.x = vd(f.x + 1, zp->x);
		nb--;
	}
}

void				xplosion(int x, int y, t_zaap *zp, int type)
{
	int		mod;
	t_fill	fill;

	mod = 1;
	fill.min = 5;
	fill.max = 10;
	fill.x = x;
	fill.y = y;
	add_res(zp->map[y][x].ressources, rand_a_b(fill.min, fill.max), type);
	while (mod <= 10)
	{
		line_ns(fill, mod, zp, type);
		line_ew(fill, mod, zp, type);
		line_sn(fill, mod, zp, type);
		line_we(fill, mod, zp, type);
		if (fill.min)
			fill.min--;
		if (fill.max > 4)
			fill.max--;
		mod++;
	}
}

void				mine_xplode(t_zaap *zp)
{
	int			type;
	int			x;
	int			y;

	type = 1;
	while (type < 7)
	{
		x = rand_a_b(0, zp->x);
		y = rand_a_b(0, zp->y);
		xplosion(x, y, zp, type);
		type++;
	}
}

void				fill_map(t_zaap *zp)
{
	int		nbtm;

	nbtm = 0;
	nbtm = get_nb_team(zp->teams);//a faire
	while (nbtm)
	{
		mine_xplode(zp);
		nbtm--;
	}
}

void				get_map(t_zaap *zp)
{
	int		y;

	y = 0;
	if (zp->x < MIN_X || zp->y < MIN_Y)
		zaap_error(-4);
	if ((zp->map = (t_map**)malloc(sizeof(t_map*) * zp->y)) == NULL)
		zaap_error(-2);
	while (y < zp->y)
	{
		zp->map[y] = (t_map*)malloc(sizeof(t_map) * zp->x);
		y++;
	}
	init_map(zp);
	fill_map(zp);
}
