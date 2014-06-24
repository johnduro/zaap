/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbz_res.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:33:26 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:35:19 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"
#include "libft.h"

void		dbz_thy(int nb, int x, int y, t_zaap *zaap)
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
		change_thystame(&tmp, zaap, 1);
		map = zaap->map[ny][nx];
		if (zaap->gfx)
			send_spot(map, zaap->gfx, ny, nx);
		nb--;
	}
}

void		dbz_phi(int nb, int x, int y, t_zaap *zaap)
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
		change_phiras(&tmp, zaap, 1);
		map = zaap->map[ny][nx];
		if (zaap->gfx)
			send_spot(map, zaap->gfx, ny, nx);
		nb--;
	}
}

void		dbz_men(int nb, int x, int y, t_zaap *zaap)
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
		change_mendiane(&tmp, zaap, 1);
		map = zaap->map[ny][nx];
		if (zaap->gfx)
			send_spot(map, zaap->gfx, ny, nx);
		nb--;
	}
}

void		dbz_sib(int nb, int x, int y, t_zaap *zaap)
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
		change_sibur(&tmp, zaap, 1);
		map = zaap->map[ny][nx];
		if (zaap->gfx)
			send_spot(map, zaap->gfx, ny, nx);
		nb--;
	}
}

void		dbz_der(int nb, int x, int y, t_zaap *zaap)
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
		change_deraumere(&tmp, zaap, 1);
		map = zaap->map[ny][nx];
		if (zaap->gfx)
			send_spot(map, zaap->gfx, ny, nx);
		nb--;
	}
}
