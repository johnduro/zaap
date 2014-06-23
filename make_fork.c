/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:33:54 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 17:17:54 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

static t_egg	*init_egg(int x, int y, int time)
{
	t_egg		*new;
	static int	nb = 1;

	if ((new = (t_egg *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->ok = 0;
	new->x = x;
	new->y = y;
	new->nb = nb;
	new->next = NULL;
	new->prev = NULL;
	action_time(&(new->hatch), time, 600);
	nb++;
	return (new);
}

void			add_caps_map(t_caps *caps, int x, int y, t_zaap *zaap)
{
	t_caps		*bwscps;

	bwscps = zaap->map[y][x].list;
	if (zaap->map[y][x].list == NULL)
		zaap->map[y][x].list = caps;
	else
	{
		while (bwscps->next)
			bwscps = bwscps->next;
		bwscps->next = caps;
		caps->prev = bwscps;
	}
}

static void		add_egg_map(t_egg *egg, t_zaap *zaap)
{
	t_caps		*caps;

	caps = init_caps(NULL, egg);
	add_caps_map(caps, egg->x, egg->y, zaap);
}

static void		add_egg_team(t_egg *egg, t_team *team)
{
	t_egg		*bwseg;

	if (team->eggs == NULL)
		team->eggs = egg;
	else
	{
		bwseg = team->eggs;
		while (bwseg->next)
			bwseg = bwseg->next;
		bwseg->next = egg;
		egg->prev = bwseg;
	}
}

int				make_fork(t_action *act, t_player *pl, t_zaap *zaap)
{
	t_egg		*egg;
	char		tmp[BUFF + 1];

	(void)act;
	egg = init_egg(pl->pos_x, pl->pos_y, zaap->time);
	add_egg_team(egg, pl->p_team);
	add_egg_map(egg, zaap);
	if (zaap->gfx)
	{
		sprintf(tmp, "enw #%d #%d %d %d\n", egg->nb, pl->sock, egg->x, egg->y);
		add_to_gfx_buf(zaap->gfx, tmp);
	}
	add_player_buff(pl, "ok\n");
	return (0);
}
