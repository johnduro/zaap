/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbz_5_7_lin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:29:57 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:50:09 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"
#include "libft.h"

void		dbz_lin(int nb, int x, int y, t_zaap *zaap)
{
	t_player	tmp;
	int			nx;
	int			ny;
	t_map		map;

	tmp.pos_x = x;
	tmp.pos_y = y;
	while (nb > 0)
	{
		nx = rand_a_b(0, zaap->x);
		ny = rand_a_b(0, zaap->y);
		tmp.inventory = zaap->map[ny][nx].ressources;
		change_linemate(&tmp, zaap, 1);
		map = zaap->map[ny][nx];
		if (zaap->gfx)
			send_spot(map, zaap->gfx, ny, nx);
		nb--;
	}
}

void		dbz_lvl7(int x, int y, t_zaap *zaap)
{
	dbz_lin(2, x, y, zaap);
	dbz_der(2, x, y, zaap);
	dbz_sib(2, x, y, zaap);
	dbz_men(2, x, y, zaap);
	dbz_phi(2, x, y, zaap);
	dbz_thy(1, x, y, zaap);
}

void		dbz_lvl6(int x, int y, t_zaap *zaap)
{
	dbz_lin(1, x, y, zaap);
	dbz_der(2, x, y, zaap);
	dbz_sib(3, x, y, zaap);
	dbz_phi(1, x, y, zaap);
}

void		dbz_lvl5(int x, int y, t_zaap *zaap)
{
	dbz_lin(1, x, y, zaap);
	dbz_der(2, x, y, zaap);
	dbz_sib(1, x, y, zaap);
	dbz_men(3, x, y, zaap);
}
