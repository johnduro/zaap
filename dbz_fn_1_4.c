/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbz_fn_1_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:26:17 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:50:27 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"
#include "libft.h"

static void		dbz_lvl4(int x, int y, t_zaap *zaap)
{
	dbz_lin(2, x, y, zaap);
	dbz_der(1, x, y, zaap);
	dbz_sib(2, x, y, zaap);
	dbz_phi(1, x, y, zaap);
}

static void		dbz_lvl3(int x, int y, t_zaap *zaap)
{
	dbz_lin(2, x, y, zaap);
	dbz_sib(1, x, y, zaap);
	dbz_phi(2, x, y, zaap);
}

static void		dbz_lvl2(int x, int y, t_zaap *zaap)
{
	dbz_lin(1, x, y, zaap);
	dbz_der(1, x, y, zaap);
	dbz_sib(1, x, y, zaap);
}

static void		dbz_lvl1(int x, int y, t_zaap *zaap)
{
	dbz_lin(1, x, y, zaap);
}

void			dbz_fn(t_player *pl, t_zaap *zaap)
{
	t_map		map;

	map = zaap->map[pl->pos_y][pl->pos_x];
	if (pl->lvl == 1)
		dbz_lvl1(pl->pos_x, pl->pos_y, zaap);
	else if (pl->lvl == 2)
		dbz_lvl2(pl->pos_x, pl->pos_y, zaap);
	else if (pl->lvl == 3)
		dbz_lvl3(pl->pos_x, pl->pos_y, zaap);
	else if (pl->lvl == 4)
		dbz_lvl4(pl->pos_x, pl->pos_y, zaap);
	else if (pl->lvl == 5)
		dbz_lvl5(pl->pos_x, pl->pos_y, zaap);
	else if (pl->lvl == 6)
		dbz_lvl6(pl->pos_x, pl->pos_y, zaap);
	else if (pl->lvl == 7)
		dbz_lvl7(pl->pos_x, pl->pos_y, zaap);
	if (zaap->gfx)
		send_spot(map, zaap->gfx, pl->pos_y, pl->pos_x);
}
