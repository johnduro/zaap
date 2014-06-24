/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_broadcast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:55:10 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 17:35:39 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "zaap.h"
#include "libft.h"

int				ft_distance_carre(t_player *p1, t_player *p2)
{
	int		ret;
	int		x;
	int		y;

	x = (p1->pos_x - p2->pos_x);
	y = (p1->pos_y - p2->pos_y);
	ret = (x * x) + (y * y);
	return (ret);
}

t_player		ft_find_pos(t_zaap *zaap, t_player *src, int plan)
{
	t_player		pos2;

	pos2.pos_x = src->pos_x;
	pos2.pos_y = src->pos_y;
	if (((plan + 3) % 4) != 0 && plan != 0)
	{
		if (plan < 5)
			pos2.pos_x -= zaap->x;
		else
			pos2.pos_x += zaap->x;
	}
	if (((plan + 1) % 4) != 0 && plan != 0)
	{
		if ((plan % 8) < 3)
			pos2.pos_y -= zaap->y;
		else
			pos2.pos_y += zaap->y;
	}
	return (pos2);
}

int				ft_direction(t_player *src, t_player *dest)
{
	int		ret;
	int		dx;
	int		dy;

	dx = (src->pos_x - dest->pos_x) * (src->pos_x - dest->pos_x);
	dy = (src->pos_y - dest->pos_y) * (src->pos_y - dest->pos_y);
	ret = 1;
	if (dx == dy)
		ret += 1;
	if (src->pos_x < dest->pos_x
		&& (dx > dy || (dx == dy && src->pos_y > dest->pos_y)))
		ret += 2;
	else if (src->pos_y > dest->pos_y
		&& (dx < dy || (dx == dy && src->pos_x > dest->pos_x)))
		ret += 4;
	else if (src->pos_x > dest->pos_x
		&& (dx > dy || (dx == dy && src->pos_y < dest->pos_y)))
		ret += 6;
	if (dest->dir == 2)
		ret = ((ret + 1) % 8) + 1;
	else if (dest->dir == 3)
		ret = ((ret + 3) % 8) + 1;
	else if (dest->dir == 4)
		ret = ((ret + 5) % 8) + 1;
	return (ret);
}

int				ft_broadcast(t_zaap *zaap, t_player *src, t_player *dest)
{
	int			plan;
	t_player	tmp;
	int			i;
	int			min;
	int			ret;

	if ((min = ft_distance_carre(src, dest)) == 0)
		return (0);
	i = 1;
	plan = 0;
	while (i <= 8)
	{
		tmp = ft_find_pos(zaap, src, i);
		ret = ft_distance_carre(&tmp, dest);
		if (ret < min)
		{
			min = ret;
			plan = i;
		}
		i++;
	}
	tmp = ft_find_pos(zaap, src, plan);
	ret = ft_direction(&tmp, dest);
	return (ret);
}
