/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_gfx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 18:24:23 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/14 19:31:52 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

void		send_dim_gfx(t_gfx *gfx, t_zaap *zaap)
{
	char	*tmp;
	char	*tmp2;

	tmp = get_pos(zaap->x, zaap->y);
	tmp2 = ft_strjoin("msz ", tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, "\n");
	free(tmp2);
	add_to_gfx_buf(gfx, tmp);
	free(tmp);
}

int			gfx_teams_name(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	(void)tab;
	send_teams_gfx(gfx, zaap);
	return (0);
}

int			gfx_all_map(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	(void)tab;
	send_all_map(gfx, zaap);
	return (0);
}

int			gfx_spot_content(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	int		x;
	int		y;

	if (!tab[1] || !tab[2])
		return (-1);
	x = ft_atoi(tab[1]);
	y = ft_atoi(tab[2]);
	if (x < 0 || x >= zaap->x || y < 0 || y >= zaap->y)
		return (-1);
	send_spot(zaap->map[y][x], gfx, y, x);
	return (0);
}

int			gfx_map_size(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	(void)tab;
	send_dim_gfx(gfx, zaap);
	return (0);
}
