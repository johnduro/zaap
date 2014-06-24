/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_add_inc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:42:56 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:46:16 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

static t_inc	*init_inc(int count, struct timeval tm)
{
	t_inc		*new;

	if ((new = (t_inc *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->nb = count;
	new->check = -2;
	new->ref.tv_sec = tm.tv_sec;
	new->ref.tv_usec = tm.tv_usec;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void			add_new_inc(t_action *act, t_zaap *z, int c)
{
	t_inc		*inc;
	t_inc		*bwsi;

	inc = init_inc(c, act->finish);
	if (z->inc == NULL)
		z->inc = inc;
	else
	{
		bwsi = z->inc;
		while (bwsi->next)
			bwsi = bwsi->next;
		bwsi->next = inc;
		inc->prev = bwsi;
	}
}

int				check_lvl_elev(t_caps *bwscps, int lvl, int nb)
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

int				check_elev(t_player *pl, t_zaap *zaap)
{
	int		ret;

	ret = -1;
	if (pl->lvl == 1)
		ret = check_lvl1(pl, zaap);
	else if (pl->lvl == 2)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 3)
		ret = check_lvl3(pl, zaap);
	else if (pl->lvl == 4)
		ret = check_lvl4(pl, zaap);
	else if (pl->lvl == 5)
		ret = check_lvl5(pl, zaap);
	else if (pl->lvl == 6)
		ret = check_lvl6(pl, zaap);
	else if (pl->lvl == 7)
		ret = check_lvl7(pl, zaap);
	else if (pl->lvl == 8)
		ret = -1;
	return (ret);
}
