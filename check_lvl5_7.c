/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lvl5_7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 15:57:51 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/19 15:58:49 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"

int			check_lvl7(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 6))
		return (-1);
	if (spot->linemate < 2 || spot->deraumere < 2 || spot->sibur < 2
		|| spot->mendiane < 2 || spot->phiras < 1 || spot->thystame < 1)
		return (-1);
	return (0);
}

int			check_lvl6(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 6))
		return (-1);
	if (spot->linemate < 1 || spot->deraumere < 2
		|| spot->sibur < 3 || spot->phiras < 1)
		return (-1);
	return (0);
}

int			check_lvl5(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 4))
		return (-1);
	if (spot->linemate < 1 || spot->deraumere < 2
		|| spot->sibur < 1 || spot->mendiane < 3)
		return (-1);
	return (0);
}
