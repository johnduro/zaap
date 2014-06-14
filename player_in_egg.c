/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_in_egg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:59:23 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/12 17:05:37 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

void			remove_egg_map(t_egg *egg, t_zaap *zaap)
{
	t_caps		*bwscps;

	bwscps = zaap->map[egg->y][egg->x].list;
	while (bwscps)
	{
		if (bwscps->egg == egg)
		{
			if (bwscps->prev == NULL && bwscps->next == NULL)
				zaap->map[egg->y][egg->x].list = NULL;
			else if (bwscps->prev == NULL && bwscps->next)
			{
				zaap->map[egg->y][egg->x].list = bwscps->next;
				bwscps->prev = NULL;
			}
			else if (bwscps->prev && bwscps->next)
			{
				bwscps->next->prev = bwscps->prev;
				bwscps->prev->next = bwscps->next;
			}
			else if (bwscps->prev && bwscps->next == NULL)
				bwscps->prev->next = NULL;
			free(bwscps);
			return ;
		}
		bwscps = bwscps->next;
	}
}

t_egg			*egg_rdy(t_egg *bwsegg)
{
	while (bwsegg)
	{
		if (is_time_yet(bwsegg->hatch)) //A REFAIRE
			return (bwsegg);
		bwsegg = bwsegg->next;
	}
	return (NULL);
}

static void		remove_egg_team(t_egg *egg, t_team *team)
{
	if (egg->prev == NULL && egg->next == NULL)
		team->eggs = NULL;
	else if (egg->prev == NULL && egg->next)
	{
		team->eggs = egg->next;
		egg->next->prev = NULL;
	}
	else if (egg->prev && egg->next)
	{
		egg->prev->next = egg->next;
		egg->next->prev = egg->prev;
	}
	else if (egg->prev && egg->next == NULL)
		egg->prev->next = NULL;
	free(egg);
}

void			place_player_in_egg(t_team *t, t_player *n, t_egg *e, t_zaap *z)
{
	n->pos_x = e->x;
	n->pos_y = e->y;
	add_player_to_map(n, z);
	remove_egg_map(e, z);
	remove_egg_team(e, t);
}
