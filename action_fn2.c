/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_fn2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 17:59:23 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/19 18:53:14 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"

int				player_broadcast(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(BRD, tab[1], 7);
	add_action_player(action, pl, zaap);
	return (0);
}

int				player_expulse(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(EXP, tab[1], 7);
	add_action_player(action, pl, zaap);
	return (0);
}

int				player_drop(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(PUT, tab[1], 7);
	add_action_player(action, pl, zaap);
	return (0);
}

int				player_take(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(TAK, tab[1], 7);
	add_action_player(action, pl, zaap);
	return (0);
}
