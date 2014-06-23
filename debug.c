/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:09:36 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 16:17:56 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "zaap.h"
#include "libft.h"

static void		print_case(t_map yolo, int nb, int x, int y)
{
	printf("Case n*%d pos[%d][%d]\n", nb, x, y);
	printf("Linemate %d, ", yolo.ressources->linemate);
	printf("deraumere %d, ", yolo.ressources->deraumere);
	printf("sibur %d, ", yolo.ressources->sibur);
	printf("mendiane %d, ", yolo.ressources->mendiane);
	printf("phiras %d, ", yolo.ressources->phiras);
	printf("thystame %d\n", yolo.ressources->thystame);
}

static void		debug_map(t_map **map, t_zaap *zaap)
{
	int	i;
	int	j;
	int	all;

	i = 0;
	j = 0;
	all = 1;
	while (i < zaap->y)
	{
		j = 0;
		while (j < zaap->x)
		{
			print_case(map[i][j], all, i, j);
			all++;
			j++;
		}
		i++;
	}
}

static void		print_teams(t_team *team)
{
	int	nb;

	nb = 1;
	while (team)
	{
		printf("team n*%d: %s\n", nb, team->name);
		nb++;
		team = team->next;
	}
}

void			debug_1(t_zaap *zaap)
{
	printf("Sock = %d\n", zaap->sock);
	printf("x = %d || y = %d\n", zaap->x, zaap->y);
	printf("nb_start = %d\n", zaap->nb_start);
	printf("time = %d\n", zaap->time);
	debug_map(zaap->map, zaap);
	if (zaap->teams)
		print_teams(zaap->teams);
}
