/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_incant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:31:40 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 16:14:55 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

void		send_suc_elv_gfx(t_player *pl, t_gfx *gfx)
{
	char		tmp[BUFF + 1];

	sprintf(tmp, "pie %d %d 1\n", pl->pos_x, pl->pos_y);
	add_to_gfx_buf(gfx, tmp);
}

t_inc		*find_inc(struct timeval tm, t_zaap *zaap)
{
	t_inc	*bws;

	bws = zaap->inc;
	while (bws)
	{
		if (bws->ref.tv_sec == tm.tv_sec && bws->ref.tv_usec == tm.tv_usec)
			return (bws);
		bws = bws->next;
	}
	return (NULL);
}

void		remove_inc(t_inc *inc, t_zaap *zaap)
{
	if (inc->prev == NULL && inc->next == NULL)
		zaap->inc = NULL;
	else if (inc->prev && inc->next == NULL)
		inc->prev->next = NULL;
	else if (inc->prev && inc->next)
	{
		inc->prev->next = inc->next;
		inc->next->prev = inc->prev;
	}
	else if (inc->prev == NULL && inc->next)
	{
		inc->next->prev = NULL;
		zaap->inc = inc->next;
	}
	free(inc);
}

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

void		dbz_lvl7(int x , int y, t_zaap *zaap)
{
	dbz_lin(2, x, y, zaap);
	dbz_der(2, x, y, zaap);
	dbz_sib(2, x, y, zaap);
	dbz_men(2, x, y, zaap);
	dbz_phi(2, x, y, zaap);
	dbz_thy(1, x, y, zaap);
}

void		dbz_lvl6(int x , int y, t_zaap *zaap)
{
	dbz_lin(1, x, y, zaap);
	dbz_der(2, x, y, zaap);
	dbz_sib(3, x, y, zaap);
	dbz_phi(1, x, y, zaap);
}

void		dbz_lvl5(int x , int y, t_zaap *zaap)
{
	dbz_lin(1, x, y, zaap);
	dbz_der(2, x, y, zaap);
	dbz_sib(1, x, y, zaap);
	dbz_men(3, x, y, zaap);
}

void		dbz_lvl4(int x , int y, t_zaap *zaap)
{
	dbz_lin(2, x, y, zaap);
	dbz_der(1, x, y, zaap);
	dbz_sib(2, x, y, zaap);
	dbz_phi(1, x, y, zaap);
}

void		dbz_lvl3(int x , int y, t_zaap *zaap)
{
	dbz_lin(2, x, y, zaap);
	dbz_sib(1, x, y, zaap);
	dbz_phi(2, x, y, zaap);
}

void		dbz_lvl2(int x , int y, t_zaap *zaap)
{
	dbz_lin(1, x, y, zaap);
	dbz_der(1, x, y, zaap);
	dbz_sib(1, x, y, zaap);
}

void		dbz_lvl1(int x , int y, t_zaap *zaap)
{
	dbz_lin(1, x, y, zaap);
}

void		dbz_fn(t_player *pl, t_zaap *zaap)
{
	t_map	map;

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

int			end_of_inc(t_action *act, t_player *pl, t_zaap *zaap)
{
	t_inc	*inc;
	int		ret;

	ret = 0;
	inc = find_inc(act->finish, zaap);
	if (inc == NULL)
		return (-1);
	(inc->nb)--;
	ret = check_elev(pl, zaap);
	if (inc->nb == 0)
	{
		if (zaap->gfx)
		{
			if (ret)
				send_failed_elv_gfx(pl, zaap->gfx);
			else
				send_suc_elv_gfx(pl, zaap->gfx);
		}
		if (!ret)
			dbz_fn(pl, zaap);
		remove_inc(inc, zaap);
	}
	return (ret);
}

int			make_incant(t_action *act, t_player *pl, t_zaap *zaap)
{
//	static struct timeval		ref;
	char						tmp[BUFF + 1];

	if (end_of_inc(act, pl, zaap))
		add_player_buff(pl, "ko\n");
	else
	{
		(pl->lvl)++;
		sprintf(tmp, "niveau actuel : %d\n", pl->lvl);
		add_player_buff(pl, tmp);
		if (zaap->gfx)
		{
			sprintf(tmp, "plv #%d %d\n", pl->sock, pl->lvl);
			add_to_gfx_buf(zaap->gfx, tmp);
		}
	}
	return (0);
}

/*
int			make_incant(t_action *act, t_player *pl, t_zaap *zaap)
{
	static struct timeval		ref;
	char						tmp[BUFF + 1];

	if (ref.tv_sec != act->finish.tv_sec || ref.tv_usec != act->finish.tv_usec)
	{
		ref.tv_sec = act->finish.tv_sec;
		ref.tv_usec = act->finish.tv_usec;
		if (zaap->gfx)
			send_suc_elv_gfx(pl, zaap->gfx);
	}
	(pl->lvl)++;
	sprintf(tmp, "niveau actuel : %d\n", pl->lvl);
	add_player_buff(pl, tmp);
	if (zaap->gfx)
	{
		sprintf(tmp, "plv #%d %d\n", pl->sock, pl->lvl);
		add_to_gfx_buf(zaap->gfx, tmp);
	}
	return (0);
}
*/
