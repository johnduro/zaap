/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 17:08:39 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 17:36:23 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

void			remove_caps_player(t_caps *bwscps, t_player *pl, t_zaap *zaap)
{
	if (bwscps->prev == NULL && bwscps->next == NULL)
		zaap->map[pl->pos_y][pl->pos_x].list = NULL;
	else if (bwscps->prev == NULL && bwscps->next)
	{
		zaap->map[pl->pos_y][pl->pos_x].list = bwscps->next;
		bwscps->next->prev = NULL;
	}
	else if (bwscps->prev && bwscps->next)
	{
		bwscps->next->prev = bwscps->prev;
		bwscps->prev->next = bwscps->next;
	}
	else if (bwscps->prev && bwscps->next == NULL)
		bwscps->prev->next = NULL;
	free(bwscps);
}

void			remove_player_map(t_player *player, t_zaap *zaap)
{
	t_caps		*bwscps;

	bwscps = zaap->map[player->pos_y][player->pos_x].list;
	while (bwscps)
	{
		if (bwscps->player == player)
		{
			remove_caps_player(bwscps, player, zaap);
			return ;
		}
		bwscps = bwscps->next;
	}
}

void			add_player_to_map(t_player *pl, t_zaap *zaap)
{
	t_caps		*new_pos;

	new_pos = init_caps(pl, NULL);
	add_caps_map(new_pos, pl->pos_x, pl->pos_y, zaap);
}
