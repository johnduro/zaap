/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:10:21 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/11 16:10:23 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

static t_stock			*gen_ressources(void)
{
	t_stock	*inv;

	inv = get_inv();
	inv->food = rand_a_b(1, 11);
	inv->linemate = rand_a_b(0, 11);
	inv->deraumere = rand_a_b(0, 10);
	inv->sibur = rand_a_b(0, 9);
	inv->mendiane = rand_a_b(0, 5);
	inv->phiras = rand_a_b(0, 4);
	inv->thystame = rand_a_b(0, 3);
	return (inv);
}

static void		init_map(t_zaap *zaap)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	srand(time(NULL));
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

void			get_map(t_zaap *zaap)
{
	int	y;

	y = 0;
	if (zaap->x < 20 || zaap->y < 20)
		zaap_error(-4);
	if ((zaap->map = (t_map**)malloc(sizeof(zaap->map) * (zaap->y + 1))) == NULL)
		zaap_error(-2);
	while (y < zaap->y)
	{
		zaap->map[y] = (t_map*)malloc(sizeof(zaap->map) * (zaap->x + 1));
		y++;
	}
	init_map(zaap);
}
