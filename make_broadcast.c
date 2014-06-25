/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_broadcast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:50:52 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/25 17:35:06 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "zaap.h"
#include "libft.h"

static void		send_bc_gfx(int sock, char *str, t_gfx *gfx)
{
	char		ret[BUFF + 1];

	sprintf(ret, "pbc #%d %s\n", sock, str);
	add_to_gfx_buf(gfx, ret);
}

static void		bc_to_pl(t_action *act, t_player *s, t_player *bwspl, t_zaap *z)
{
	int			ret;
	char		tmp[BUFF + 1];

	ret = -1;
	while (bwspl)
	{
		if (bwspl != s)
		{
			ret = ft_broadcast(z, s, bwspl);
			sprintf(tmp, "message %d,%s\n", ret, act->buff);
			add_player_buff(bwspl, tmp);
			printf("sending bc to %d frm %d\n))>%s", bwspl->sock, s->sock, tmp);
		}
		bwspl = bwspl->next;
	}
}

int				make_broadcast(t_action *act, t_player *pl, t_zaap *zaap)
{
	t_team		*bwst;

	bwst = zaap->teams;
	while (bwst)
	{
		if (bwst->first)
			bc_to_pl(act, pl, bwst->first, zaap);
		bwst = bwst->next;
	}
	if (zaap->gfx)
		send_bc_gfx(pl->sock, act->buff, zaap->gfx);
	add_player_buff(pl, "ok\n");
	return (0);
}
