/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_elv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 15:49:27 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/19 17:03:19 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

static void			add_action_front(t_action *act, t_player *pl)
{
	t_action	*cpy;

	cpy = init_action(ELV, NULL, 300);
	cpy->finish.tv_sec = act->finish.tv_sec;
	cpy->finish.tv_usec = act->finish.tv_usec;
	if (pl->a_first == NULL)
	{
		pl->a_first = cpy;
		pl->a_last = cpy;
	}
	else
	{
		cpy->next = pl->a_first;
		pl->a_first->prev = cpy;
		pl->a_first = cpy;
	}
}

int					check_lvl_elev(t_caps *bwscps, int lvl, int nb)
{
	int		count;

	count = 0;
	while (bwscps)
	{
		if (bwscps->player && bwscps->player->lvl == lvl)
			count++;
		bwscps = bwscps->next;
	}
	if (count < nb)
		return (-1);
	return (0);
}

static int			check_elev(t_player *pl, t_zaap *zaap)
{
	int		ret;

	ret = -1;
	if (pl->lvl == 1)
		ret = check_lvl1(pl, zaap);
	else if (pl->lvl == 2)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 3)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 4)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 5)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 6)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 7)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 8)
		ret = -1;
	return (ret);
}


static void			send_start_elv_gfx(t_player *pl, t_zaap *zaap)
{
	char		tmp[BUFF + 1];
	char		*tmp2;
	char		*tmp3;
	char		*tmp4;
	t_caps		*bwscps;

	bwscps = zaap->map[pl->pos_y][pl->pos_x].list;
	sprintf(tmp, "pic %d %d %d #%d ", pl->pos_x, pl->pos_y, pl->lvl, pl->sock);
	tmp2 = ft_strnew(0);
	while (bwscps)
	{
		if (bwscps->player && bwscps->player->lvl == pl->lvl
			&& bwscps->player != pl)
		{
			tmp3 = ft_itoa(bwscps->player->sock);
			tmp4 = ft_strjoin("#", tmp3);
			ft_addnstr(&tmp2, 1, 1, tmp4);
			ft_free_all_four(tmp3, tmp4, NULL, NULL);
		}
		bwscps = bwscps->next;
	}
	tmp3 = ft_strjoin(tmp, tmp2);
	add_to_gfx_buf(zaap->gfx, tmp3);
	ft_free_all_four(tmp3, tmp2, NULL, NULL);
}


void					start_elev(t_action *act, t_player *pl, t_zaap *zaap)
{
	t_caps		*bwscps;

	if (zaap->gfx)
		send_start_elv_gfx(pl, zaap);
	if (check_elev(pl, zaap))
	{
		add_player_buff(pl, "ko\n");
		prep_next_act(act, pl, zaap);
		if (zaap->gfx)
			send_failed_elv_gfx(pl, zaap->gfx);
	}
	else
	{
		bwscps = zaap->map[pl->pos_y][pl->pos_x].list;
		while (bwscps)
		{
			if (bwscps->player && (bwscps->player->lvl == pl->lvl))
			{
				add_player_buff(bwscps->player, "elevation en cours\n");
				if (bwscps->player != pl)
					add_action_front(act, bwscps->player);
			}
			bwscps = bwscps->next;
		}
	}
}
