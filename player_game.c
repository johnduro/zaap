/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 15:41:31 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 18:22:39 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

static t_pac		*get_parse_make(void)
{
	static t_pac	parse[] =

	{
	{AVC, &make_go},
	{DRT, &make_right},
	{GAU, &make_left},
	{SEE, &make_see},
	{INV, &make_inv},
	{TAK, &make_take},
	{PUT, &make_drop},
	{EXP, &make_expulse},
	{BRD, &make_broadcast},
	{ELV, &make_incant},
	{FRK, &make_fork},
	{CNN, &make_connect},
	{0, NULL}
	};
	return (parse);
}

void				prep_next_act(t_action *act, t_player *pl, t_zaap *zaap)
{
	if (pl->a_first->next == NULL)
	{
		pl->a_first = NULL;
		pl->a_last = NULL;
	}
	else if (pl->a_first->next)
	{
		pl->a_first = pl->a_first->next;
		pl->a_first->prev = NULL;
		action_time(&(pl->a_first->finish), zaap->time, pl->a_first->lenght);
		if (pl->a_first->type == FRK && zaap->gfx)
			send_hatching_gfx(pl->sock, zaap->gfx);
		else if (pl->a_first->type == ELV)
			start_elev(pl->a_first, pl, zaap);
	}
	free(act);
}

static void			make_action(t_action *act, t_player *pl, t_zaap *zaap)
{
	int			i;
	t_pac		*parse;

	i = 0;
	parse = get_parse_make();
	while (i < 12)
	{
		if (parse[i].type == act->type)
			parse[i].fn(act, pl, zaap);
		i++;
	}
	prep_next_act(act, pl, zaap);
}

static int			check_food(t_player *pl, t_zaap *zaap)
{
	char		ret[BUFF + 1];

	if (is_time_yet(pl->tick))
	{
		(pl->inventory->food)--;
		if (pl->inventory->food <= 0)
		{
			pl->alive = 0;
			add_player_buff(pl, "mort\n");
			if (zaap->gfx)
			{
				sprintf(ret, "pdi #%d\n", pl->sock);
				add_to_gfx_buf(zaap->gfx, ret);
			}
			return (-1);
		}
		else
			action_time(&(pl->tick), zaap->time, 126);
	}
	return (0);
}

void				player_game(t_player *pl, t_zaap *zaap)
{
	if (check_food(pl, zaap))
		return ;
	if (pl->a_first)
	{
		if (is_time_yet(pl->a_first->finish))
		{
			make_action(pl->a_first, pl, zaap);
			if (pl->nba > 0)
				pl->nba--;
		}
	}
}
