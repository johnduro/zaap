/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:48:51 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:51:45 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

void		send_dim_time(t_gfx *gfx, t_zaap *zaap)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*ret;

	tmp = ft_itoa(zaap->x);
	tmp2 = ft_strjoin("msz ", tmp);
	free(tmp);
	tmp = ft_itoa(zaap->y);
	tmp3 = ft_strjoinwsep(tmp2, tmp, ' ');
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp3, "\nsgt ");
	free(tmp3);
	tmp2 = ft_itoa(zaap->time);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	ret = ft_strjoin(tmp3, "\n");
	free(tmp3);
	add_to_gfx_buf(gfx, ret);
	free(ret);
}

char		*get_ressources(t_map map, int i)
{
	if (i == 0)
		return (ft_itoa(map.ressources->food));
	else if (i == 1)
		return (ft_itoa(map.ressources->linemate));
	else if (i == 2)
		return (ft_itoa(map.ressources->deraumere));
	else if (i == 3)
		return (ft_itoa(map.ressources->sibur));
	else if (i == 4)
		return (ft_itoa(map.ressources->mendiane));
	else if (i == 5)
		return (ft_itoa(map.ressources->phiras));
	else if (i == 6)
		return (ft_itoa(map.ressources->thystame));
	return (NULL);
}

void		send_spot(t_map map, t_gfx *gfx, int y, int x)
{
	char	ret[BUFF];
	char	*tmp;
	int		i;

	i = 0;
	ft_strcpy(ret, "bct ");
	tmp = ft_itoa(x);
	ft_strcat(ret, tmp);
	free(tmp);
	ft_strcat(ret, " ");
	tmp = ft_itoa(y);
	ft_strcat(ret, tmp);
	free(tmp);
	while (i < 7)
	{
		tmp = get_ressources(map, i);
		ft_strcat(ret, " ");
		ft_strcat(ret, tmp);
		free(tmp);
		i++;
	}
	ft_strcat(ret, "\n");
	add_to_gfx_buf(gfx, ret);
}

void		first_map_send(t_gfx *gfx, t_zaap *zaap)
{
	int		i;
	int		j;

	i = 0;
	send_dim_time(gfx, zaap);
	while (i < zaap->y)
	{
		j = 0;
		while (j < zaap->x)
		{
			send_spot(zaap->map[i][j], gfx, i, j);
			j++;
		}
		i++;
	}
}

t_gfx		*init_gfx(int sock, t_zaap *zaap)
{
	t_gfx		*new;

	if ((new = (t_gfx *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->sock = sock;
	new->to_send = 0;
	new->list = NULL;
	first_map_send(new, zaap);
	return (new);
}
