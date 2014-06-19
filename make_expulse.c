/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expulse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:28:46 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/19 17:04:28 by mle-roy          ###   ########.fr       */
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

int				make_expulse(t_action *act, t_player *pl, t_zaap *zaap)
{
	t_caps		*bwscps;
	char		flag;

	(void)act;
	flag = 0;
	bwscps = zaap->map[pl->pos_y][pl->pos_x].list;
	gfx_expulse(pl->sock, zaap->gfx);
	while (bwscps)
	{
		if (bwscps->player && (!bwscps->player->a_first
							   || bwscps->player->a_first->type != ELV))
		{
			move_player(bwscps->player, zaap);
			if (zaap->gfx)
				get_pos_player_gfx(bwscps->player, zaap->gfx);
			add_player_buff(bwscps->player, "deplacement 5\n");
			flag = 1;
		}
		bwscps = bwscps->next;
	}
	if (flag)
		add_player_buff(pl, "ok\n");
	else
		add_player_buff(pl, "ko\n");
	return (0);
}
