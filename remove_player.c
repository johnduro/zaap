/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:11:08 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:53:24 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

static void		free_actions(t_action *list)
{
	t_action	*keep;

	while (list)
	{
		keep = list->next;
		free(list);
		list = keep;
	}
}

void			remove_pl(t_player *pl, t_team *team, t_zaap *zaap)
{
	remove_player_buf(pl);
	remove_player_map(pl, zaap);
	close(pl->sock);
	if (pl->prev == NULL && pl->next == NULL)
		team->first = NULL;
	else if (pl->prev && pl->next == NULL)
		pl->prev->next = NULL;
	else if (pl->prev == NULL && pl->next)
	{
		team->first = pl->next;
		pl->next->prev = NULL;
	}
	else if (pl->prev && pl->next)
	{
		pl->prev->next = pl->next;
		pl->next->prev = pl->prev;
	}
	if (pl->inventory)
		free(pl->inventory);
	if (pl->a_first)
		free_actions(pl->a_first);
	free(pl);
}
