/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_eggs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 15:36:26 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/25 18:22:44 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

void				rotten_egg(t_egg *egg, t_team *team, t_zaap *zaap)
{
	char		ret[BUFF + 1];

	if (zaap->gfx)
	{
		sprintf(ret, "edi #%d\n", egg->nb);
		add_to_gfx_buf(zaap->gfx, ret);
	}
	remove_egg_map(egg, zaap);
	remove_egg_team(egg, team);
	if (team->places)
		(team->places)--;
}

static void			hatching_egg(t_egg *egg, t_team *team, t_zaap *zaap)
{
	char		ret[BUFF + 1];

	egg->ok = 1;
	team->places++;
	action_time(&(egg->hatch), zaap->time, 1260);
	if (zaap->gfx)
	{
		sprintf(ret, "eht #%d\n", egg->nb);
		add_to_gfx_buf(zaap->gfx, ret);
	}
}

void				check_eggs(t_team *team, t_zaap *zaap)
{
	t_egg		*bwseg;
	t_egg		*keep;

	if (team->eggs == NULL)
		return ;
	bwseg = team->eggs;
	while (bwseg)
	{
		keep = bwseg->next;
		if (!bwseg->ok && is_time_yet(bwseg->hatch))
			hatching_egg(bwseg, team, zaap);
		else if (bwseg->ok && is_time_yet(bwseg->hatch))
			rotten_egg(bwseg, team, zaap);
		bwseg = keep;
	}
}
