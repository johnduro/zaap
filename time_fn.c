/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 17:58:15 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/14 19:28:35 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include "zaap.h"
#include "libft.h"

void			send_time_gfx(t_gfx *gfx, t_zaap *zaap)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(zaap->time);
	tmp2 = ft_strjoin("sgt ", tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, "\n");
	free(tmp2);
	add_to_gfx_buf(gfx, tmp);
	free(tmp);
}

void			action_time(struct timeval *res, int time, int lenght)
{
	struct timeval		cur;
	struct timeval		add;

	if (lenght == 0)
	{
		gettimeofday(res, NULL);
		return ;
	}
	gettimeofday(&cur, NULL);
	if (time <= 1)
	{
		add.tv_sec = 1 * lenght;
		add.tv_usec = 0;
	}
	else
	{
		add.tv_sec = 0;
		add.tv_usec = ((1000000 / time) * lenght);
	}
	timeradd(&cur, &add, res);
}

int				is_time_yet(struct timeval ok)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	if (time.tv_sec < ok.tv_sec)
		return (0);
	else if (time.tv_sec == ok.tv_sec)
	{
		if (time.tv_usec < ok.tv_usec)
			return (0);
		else
			return (1);
	}
	else if (time.tv_sec > ok.tv_sec)
		return (1);
	return (0);
}

int				gfx_set_time(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	int		new;

	(void)gfx;
	if (!tab[1])
		return (-1);
	if ((new = ft_atoi(tab[1])) < 1)
		return (-1);
	zaap->time = new;
	return (0);
}

int				gfx_get_time(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	(void)tab;
	send_time_gfx(gfx, zaap);
	return (0);
}
