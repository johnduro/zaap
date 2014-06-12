/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 17:08:39 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/12 17:08:41 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

void					add_player_to_map(t_player *player, t_zaap *zaap)
{
	t_caps		*bwscps;
	t_caps		*new_pos;

	new_pos = init_caps(player, NULL);
	bwscps = zaap->map[player->pos_y][player->pos_x].list;
	if (bwscps == NULL)
		zaap->map[player->pos_y][player->pos_x].list = new_pos;
	else
	{
		while (bwscps->next)
			bwscps = bwscps->next;
		bwscps->next = new_pos;
		new_pos->prev = bwscps;
	}
}