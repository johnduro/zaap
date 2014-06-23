/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_incant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:31:40 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 15:54:26 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "zaap.h"
#include "libft.h"

void		send_suc_elv_gfx(t_player *pl, t_gfx *gfx)
{
	char		tmp[BUFF + 1];

	sprintf(tmp, "pie %d %d 1\n", pl->pos_x, pl->pos_y);
	add_to_gfx_buf(gfx, tmp);
}

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
