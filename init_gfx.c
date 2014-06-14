/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gfx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 19:59:46 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/14 19:59:47 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

void				send_teams_gfx(t_gfx *gfx, t_zaap *zaap)
{
	t_team		*bwst;
	char		*tmp;
	char		*to_send;

	bwst = zaap->teams;
	while (bwst)
	{
		tmp = ft_strjoin("tna ", bwst->name);
		to_send = ft_strjoin(tmp, "\n");
		free(tmp);
		add_to_gfx_buf(gfx, to_send);
		free(to_send);
		bwst = bwst->next;
	}
}

static void			send_all_players(t_gfx *gfx, t_zaap *zaap)
{
	t_team		*bwst;
	t_player	*bwspl;

	bwst = zaap->teams;
	while (bwst)
	{
		if (bwst->first)
		{
			bwspl = bwst->first;
			while (bwspl)
			{
				send_new_player(bwspl, gfx, bwst);
				bwspl = bwspl->next;
			}
		}
		bwst = bwst->next;
	}
}

void				send_all_map(t_gfx *gfx, t_zaap *zaap)
{
	int		i;
	int		j;

	i = 0;
	while (i < zaap->y)
	{
		j = 0;
		while (j < zaap->x)
		{
			send_spot(zaap->map[i][j], gfx, i, j);
			j++;
		}
		i++;
	}
}

static void			first_map_send(t_gfx *gfx, t_zaap *zaap)
{
	send_dim_gfx(gfx, zaap);
	send_time_gfx(gfx, zaap);
	send_all_map(gfx, zaap);
	send_teams_gfx(gfx, zaap);
	send_all_players(gfx, zaap);
}

t_gfx				*init_gfx(int sock, t_zaap *zaap)
{
	t_gfx		*new;

	if ((new = (t_gfx *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->sock = sock;
	new->to_send = 0;
	new->list = NULL;
	first_map_send(new, zaap);
	return (new);
}
