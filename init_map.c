/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:10:21 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:51:02 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

t_caps				*init_caps(t_player *player, t_egg *egg)
{
	t_caps		*new;

	if ((new = (t_caps *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->player = NULL;
	new->egg = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (player)
		new->player = player;
	else if (egg)
		new->egg = egg;
	return (new);
}

static t_stock		*gen_ressources(void)
{
	t_stock		*inv;

	inv = get_inv();
	inv->food = rand_a_b(1, 11);
	return (inv);
}

static void			init_map(t_zaap *zaap)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	srandom(time(NULL));
	while (i < zaap->y)
	{
		j = 0;
		while (j < zaap->x)
		{
			zaap->map[i][j].ressources = gen_ressources();
			zaap->map[i][j].list = NULL;
			j++;
		}
		i++;
	}
}

void				get_map(t_zaap *zp)
{
	int		y;

	y = 0;
	if (zp->x < MIN_X || zp->y < MIN_Y)
		zaap_error(-4);
	if ((zp->map = (t_map**)malloc(sizeof(t_map*) * zp->y)) == NULL)
		zaap_error(-2);
	while (y < zp->y)
	{
		if ((zp->map[y] = (t_map*)malloc(sizeof(t_map) * zp->x)) == NULL)
			zaap_error(-2);
		y++;
	}
	init_map(zp);
	fill_map(zp);
}
