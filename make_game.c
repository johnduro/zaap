/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:54:43 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 21:09:45 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "zaap.h"
#include "libft.h"

static int		check_win(t_team *team, t_zaap *zaap)
{
	t_player	*bwspl;
	int			count;
	char		ret[BUFF + 1];

	bwspl = team->first;
	count = 0;
	while (bwspl)
	{
		if (bwspl && bwspl->lvl == 8)
			count++;
		bwspl = bwspl->next;
	}
	if (count >= 6)
	{
		if (zaap->gfx)
		{
			sprintf(ret, "seg %s\n", team->name);
			add_to_gfx_buf(zaap->gfx, ret);
		}
		return (1);
	}
	return (0);
}

int				make_game(t_zaap *zaap)
{
	t_team		*bwst;
	t_player	*bwspl;

	bwst = zaap->teams;
	while (bwst)
	{
		if (check_win(bwst, zaap))
			return (1);
		check_eggs(bwst, zaap);
		bwspl = bwst->first;
		while (bwspl)
		{
			player_game(bwspl, zaap);
			bwspl = bwspl->next;
		}
		bwst = bwst->next;
	}
	return (0);
}
