/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_fn1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 17:56:32 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 14:47:50 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"

int				player_inv(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(INV, tab[1], 1);
	add_action_player(action, pl, zaap);
	return (0);
}

int				player_see(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(SEE, tab[1], 7);
	add_action_player(action, pl, zaap);
	return (0);
}

int				player_left(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(GAU, tab[1], 7);
	add_action_player(action, pl, zaap);
	return (0);
}

int				player_right(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(DRT, tab[1], 7);
	add_action_player(action, pl, zaap);
	return (0);
}

int				player_go(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(AVC, tab[1], 7);
	add_action_player(action, pl, zaap);
	return (0);
}
