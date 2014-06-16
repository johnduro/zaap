/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_fn3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 18:01:21 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/16 20:47:48 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"

int				player_connect(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(CNN, tab[1], 0);
	add_action_player(action, pl, zaap);
	return (0);
}

int				player_fork(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(FRK, tab[1], 42);
	add_action_player(action, pl, zaap);
	return (0);
}

int				player_incant(char **tab, t_player *pl, t_zaap *zaap)
{
	t_action	*action;

	if (pl->nba >= 10)
		return (-1);
	action = init_action(ELV, tab[1], 300);
	add_action_player(action, pl, zaap);
	return (0);
}
