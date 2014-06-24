/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_incant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:31:40 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:52:36 by mle-roy          ###   ########.fr       */
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

int			end_of_inc(t_action *act, t_player *pl, t_zaap *zaap)
{
	t_inc	*inc;

	inc = find_inc(act->finish, zaap);
	if (inc == NULL)
		return (-1);
	(inc->nb)--;
	if (inc->check == -2)
		inc->check = check_elev(pl, zaap);
	if (inc->nb == 0)
	{
		if (zaap->gfx)
		{
			if (inc->check)
				send_failed_elv_gfx(pl, zaap->gfx);
			else
				send_suc_elv_gfx(pl, zaap->gfx);
		}
		if (!(inc->check))
			dbz_fn(pl, zaap);
		remove_inc(inc, zaap);
	}
	return (inc->check);
}

int			make_incant(t_action *act, t_player *pl, t_zaap *zaap)
{
	char			tmp[BUFF + 1];

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
