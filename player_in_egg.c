/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_in_egg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:59:23 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/25 18:34:00 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

void			remove_egg_map(t_egg *egg, t_zaap *zaap)
{
	t_caps		*bwscps;

	bwscps = zaap->map[egg->y][egg->x].list;
	while (bwscps)
	{
		if (bwscps && bwscps->egg && bwscps->egg == egg)
		{
			remove_dat_caps(bwscps, egg, zaap);
			return ;
		}
		bwscps = bwscps->next;
	}
}

t_egg			*egg_rdy(t_egg *bwsegg)
{
	while (bwsegg)
	{
		if (bwsegg->ok)
			return (bwsegg);
		bwsegg = bwsegg->next;
	}
	return (NULL);
}

void			remove_egg_team(t_egg *egg, t_team *team)
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

void			send_egg_connect(int sock, t_gfx *gfx)
{
	char	tmp[BUFF + 1];

	sprintf(tmp, "ebo #%d\n", sock);
	add_to_gfx_buf(gfx, tmp);
}

void			place_player_egg(t_team *t, t_player *n, t_egg *e, t_zaap *z)
{
	n->pos_x = e->x;
	n->pos_y = e->y;
	add_player_to_map(n, z);
	if (z->gfx)
		send_egg_connect(e->nb, z->gfx);
	remove_egg_map(e, z);
	remove_egg_team(e, t);
}
