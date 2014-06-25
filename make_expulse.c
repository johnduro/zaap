/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expulse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:28:46 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/25 18:28:45 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "zaap.h"
#include "libft.h"

static void		gfx_expulse(int sock, t_gfx *gfx)
{
	char		ret[BUFF + 1];

	sprintf(ret, "pex #%d\n", sock);
	add_to_gfx_buf(gfx, ret);
}

void			send_expulse_pl(t_player *v, t_player *e)
{
	if (e->dir == v->dir)
		add_player_buff(v, "deplacement 5\n");
	else if ((e->dir == NORTH && v->dir == SOUTH)
	|| (e->dir == EAST && v->dir == WEST)
	|| (e->dir == SOUTH && v->dir == NORTH)
	|| (e->dir == WEST && v->dir == EAST))
		add_player_buff(v, "deplacement 1\n");
	else if ((e->dir == NORTH && v->dir == WEST)
	|| (e->dir == EAST && v->dir == NORTH)
	|| (e->dir == SOUTH && v->dir == EAST)
	|| (e->dir == WEST && v->dir == SOUTH))
		add_player_buff(v, "deplacement 3\n");
	else if ((e->dir == NORTH && v->dir == EAST)
	|| (e->dir == EAST && v->dir == SOUTH)
	|| (e->dir == SOUTH && v->dir == WEST)
	|| (e->dir == WEST && v->dir == NORTH))
		add_player_buff(v, "deplacement 7\n");
}

static void		send_ok(t_player *pl, int flag)
{
	if (flag)
		add_player_buff(pl, "ok\n");
	else
		add_player_buff(pl, "ko\n");
}

int				make_expulse(t_action *act, t_player *pl, t_zaap *zaap)
{
	t_caps		*bwscps;
	char		flag;

	(void)act;
	flag = 0;
	bwscps = zaap->map[pl->pos_y][pl->pos_x].list;
	if (zaap->gfx)
		gfx_expulse(pl->sock, zaap->gfx);
	while (bwscps)
	{
		if (bwscps->player && bwscps->player != pl)
		{
			move_player(bwscps->player, zaap, pl->dir);
			if (zaap->gfx)
				get_pos_player_gfx(bwscps->player, zaap->gfx);
			send_expulse_pl(bwscps->player, pl);
			flag = 1;
		}
		bwscps = bwscps->next;
	}
	send_ok(pl, flag);
	return (0);
}
