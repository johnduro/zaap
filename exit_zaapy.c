/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_zaapy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/25 17:37:56 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/25 18:21:25 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "zaap.h"

void		free_map(t_zaap *z)
{
	int		i;

	i = 0;
	while (i < z->y)
	{
		free(z->map[i]);
		z->map[i] = NULL;
		i++;
	}
	free(z->map);
	z->map = NULL;
}

void		free_tmp(t_zaap *z)
{
	t_temp		*keep;
	t_temp		*bwstmp;

	bwstmp = z->wait;
	while (bwstmp)
	{
		keep = bwstmp->next;
		free(bwstmp);
		bwstmp = keep;
	}
}

void		free_eggs(t_team *team, t_zaap *zp)
{
	t_egg	*bwseg;
	t_egg	*keep;

	bwseg = team->eggs;
	while (bwseg)
	{
		keep = bwseg->next;
		rotten_egg(bwseg, team, zp);
		bwseg = keep;
	}
}

void		free_teams(t_zaap *z)
{
	t_team		*bwst;
	t_team		*keept;
	t_player	*bwspl;
	t_player	*keeppl;

	bwst = z->teams;
	while (bwst)
	{
		keept = bwst->next;
		bwspl = bwst->first;
		while (bwspl)
		{
			keeppl = bwspl->next;
			remove_pl(bwspl, bwst, z);
			bwspl = keeppl;
		}
		if (bwst->eggs)
			free_eggs(bwst, z);
		free(bwst);
		bwst = keept;
	}
}

void		exit_zaapy(t_zaap *zp)
{
	if (zp->wait)
		free_tmp(zp);
	if (zp->teams)
		free_teams(zp);
	if (zp->gfx)
		remove_gfx(zp);
	if (zp->map)
		free_map(zp);
	close(zp->sock);
	free(zp);
}
