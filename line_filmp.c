/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_filmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:21:11 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:22:28 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"
#include "libft.h"

void		line_ns(t_fill f, int mod, t_zaap *zp, int type)
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

void		line_ew(t_fill f, int mod, t_zaap *zp, int type)
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

void		line_sn(t_fill f, int mod, t_zaap *zp, int type)
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

void		line_we(t_fill f, int mod, t_zaap *zp, int type)
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
