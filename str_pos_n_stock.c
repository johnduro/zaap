/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_pos_n_stock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 19:19:35 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/14 19:32:19 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

char				*get_pos(int x, int y)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_itoa(x);
	tmp2 = ft_itoa(y);
	tmp3 = ft_strjoinwsep(tmp, tmp2, ' ');
	free(tmp);
	free(tmp2);
	return (tmp3);
}

static char			*get_ressources(t_stock *inv, int i)
{
	if (i == 0)
		return (ft_itoa(inv->food));
	else if (i == 1)
		return (ft_itoa(inv->linemate));
	else if (i == 2)
		return (ft_itoa(inv->deraumere));
	else if (i == 3)
		return (ft_itoa(inv->sibur));
	else if (i == 4)
		return (ft_itoa(inv->mendiane));
	else if (i == 5)
		return (ft_itoa(inv->phiras));
	else if (i == 6)
		return (ft_itoa(inv->thystame));
	return (NULL);
}

char				*get_stock(t_stock *inv)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*keep;

	i = 1;
	tmp = get_ressources(inv, 0);
	while (i < 7)
	{
		tmp2 = get_ressources(inv, i);
		keep = tmp;
		tmp = ft_strjoinwsep(tmp, tmp2, ' ');
		free(keep);
		free(tmp2);
		i++;
	}
	return (tmp);
}

char				*pos_n_stock(t_stock *inv, int x, int y)
{
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	tmp = get_pos(x, y);
	tmp2 = get_stock(inv);
	tmp3 = ft_strjoinwsep(tmp, tmp2, ' ');
	free(tmp);
	free(tmp2);
	return (tmp3);
}

void				send_spot(t_map map, t_gfx *gfx, int y, int x)
{
	char		ret[BUFF + 1];
	char		*tmp;

	ft_strcpy(ret, "bct ");
	tmp = pos_n_stock(map.ressources, x, y);
	ft_strcat(ret, tmp);
	free(tmp);
	ft_strcat(ret, "\n");
	add_to_gfx_buf(gfx, ret);
}
