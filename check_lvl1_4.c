/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lvl1_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 15:55:56 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/19 15:56:55 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"

int		check_lvl4(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 4))
		return (-1);
	if (spot->linemate < 1 || spot->deraumere < 1
		|| spot->sibur < 2 || spot->phiras < 1)
		return (-1);
	return (0);
}

int		check_lvl3(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 2))
		return (-1);
	if (spot->linemate < 2 || spot->sibur < 1 || spot->phiras < 2)
		return (-1);
	return (0);
}

int		check_lvl2(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 2))
		return (-1);
	if (spot->linemate < 1 || spot->deraumere < 1 || spot->sibur < 1)
		return (-1);
	return (0);
}

int		check_lvl1(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	if (spot->linemate < 1)
		return (-1);
	return (0);
}
