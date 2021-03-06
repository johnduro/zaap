/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see_south_north.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/19 16:22:00 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 15:51:16 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

static char		*line_north(int x, int max, int y, t_zaap *z)
{
	int		i;
	char	flag;
	char	*tmp;
	char	*ret;

	i = 0;
	flag = 1;
	ret = ft_strnew(0);
	while (i < max)
	{
		tmp = see_spot(z->map[y][x], max);
		if (flag)
			flag = 0;
		ft_strjoin_free(&ret, tmp);
		free(tmp);
		i++;
		x = vd(x + 1, z->x);
		ft_strjoin_free(&ret, ", ");
	}
	if (flag)
		ft_strjoin_free(&ret, ", ");
	return (ret);
}

char			*see_north(int x, int y, t_zaap *z, int lvl)
{
	char	*tmp;
	char	*tmp2;
	char	*keep;
	int		max;

	max = 1;
	tmp2 = ft_strnew(0);
	while (lvl >= 0)
	{
		tmp = line_north(x, max, y, z);
		keep = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		tmp2 = keep;
		lvl--;
		y = vd(y - 1, z->y);
		x = vd(x - 1, z->x);
		max += 2;
	}
	return (tmp2);
}

static char		*line_south(int x, int max, int y, t_zaap *z)
{
	int			i;
	char		flag;
	char		*tmp;
	char		*ret;

	i = 0;
	flag = 1;
	ret = ft_strnew(0);
	while (i < max)
	{
		tmp = see_spot(z->map[y][x], max);
		if (flag)
			flag = 0;
		ft_strjoin_free(&ret, tmp);
		free(tmp);
		i++;
		x = vd(x - 1, z->x);
		ft_strjoin_free(&ret, ", ");
	}
	if (flag)
		ft_strjoin_free(&ret, ", ");
	return (ret);
}

char			*see_south(int x, int y, t_zaap *z, int lvl)
{
	char	*tmp;
	char	*tmp2;
	char	*keep;
	int		max;

	max = 1;
	tmp2 = ft_strnew(0);
	while (lvl >= 0)
	{
		tmp = line_south(x, max, y, z);
		keep = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		tmp2 = keep;
		lvl--;
		y = vd(y + 1, z->y);
		x = vd(x + 1, z->x);
		max += 2;
	}
	return (tmp2);
}
