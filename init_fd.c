/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 15:20:50 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 19:19:38 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"
#include "libft.h"

static void			init_players_fd(t_player *bwspl, t_zaap *zaap)
{
	while (bwspl)
	{
		if (bwspl->to_send > 0)
			FD_SET(bwspl->sock, &zaap->fd_wr);
		else
			FD_SET(bwspl->sock, &zaap->fd_rd);
		zaap->max = ft_isgreater(zaap->max, bwspl->sock);
		bwspl = bwspl->next;
	}
}

static void			init_gfx_fd(t_zaap *zaap)
{
	if (zaap->gfx)
	{
		if (zaap->gfx->to_send > 0)
			FD_SET(zaap->gfx->sock, &zaap->fd_wr);
		else
			FD_SET(zaap->gfx->sock, &zaap->fd_rd);
		zaap->max = ft_isgreater(zaap->max, zaap->gfx->sock);
	}
}

void				init_fd(t_zaap *zaap)
{
	t_team		*bwst;
	t_temp		*bwstmp;

	zaap->max = zaap->sock;
	FD_ZERO(&zaap->fd_rd);
	FD_ZERO(&zaap->fd_wr);
	FD_SET(zaap->sock, &zaap->fd_rd);
	bwstmp = zaap->wait;
	bwst = zaap->teams;
	init_gfx_fd(zaap);
	while (bwstmp)
	{
		if (ft_strlen(bwstmp->buff_wr) > 0)
			FD_SET(bwstmp->sock, &zaap->fd_wr);
		else
			FD_SET(bwstmp->sock, &zaap->fd_rd);
		zaap->max = ft_isgreater(zaap->max, bwstmp->sock);
		bwstmp = bwstmp->next;
	}
	while (bwst)
	{
		if (bwst->first)
			init_players_fd(bwst->first, zaap);
		bwst = bwst->next;
	}
}
