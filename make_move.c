/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:02:03 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 22:53:49 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"
#include "libft.h"

void		move_player(t_player *pl, t_zaap *zaap, int dir)
{
	remove_player_map(pl, zaap);
	if (dir == NORTH)
		pl->pos_y = vd((pl->pos_y - 1), zaap->y);
	else if (dir == EAST)
		pl->pos_x = vd((pl->pos_x + 1), zaap->x);
	else if (dir == SOUTH)
		pl->pos_y = vd((pl->pos_y + 1), zaap->y);
	else if (dir == WEST)
		pl->pos_x = vd((pl->pos_x - 1), zaap->x);
	add_player_to_map(pl, zaap);
	if (zaap->gfx)
		get_pos_player_gfx(pl, zaap->gfx);
}

int			make_left(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	if (pl->dir == NORTH)
		pl->dir = WEST;
	else if (pl->dir == EAST)
		pl->dir = NORTH;
	else if (pl->dir == SOUTH)
		pl->dir = EAST;
	else if (pl->dir == WEST)
		pl->dir = SOUTH;
	if (zaap->gfx)
		get_pos_player_gfx(pl, zaap->gfx);
	add_player_buff(pl, "ok\n");
	return (0);
}

int			make_right(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	if (pl->dir == NORTH)
		pl->dir = EAST;
	else if (pl->dir == EAST)
		pl->dir = SOUTH;
	else if (pl->dir == SOUTH)
		pl->dir = WEST;
	else if (pl->dir == WEST)
		pl->dir = NORTH;
	if (zaap->gfx)
		get_pos_player_gfx(pl, zaap->gfx);
	add_player_buff(pl, "ok\n");
	return (0);
}

int			make_go(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	move_player(pl, zaap, pl->dir);
	add_player_buff(pl, "ok\n");
	return (0);
}
