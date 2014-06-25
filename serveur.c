/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:28 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/25 18:26:51 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "zaap.h"
#include "libft.h"

void	send_change(int sock, t_gfx *gfx, char flag, int obj)
{
	char	tmp[BUFF + 1];

	if (flag)
		sprintf(tmp, "pgt #%d %d\n", sock, obj);
	else
		sprintf(tmp, "pdr #%d %d\n", sock, obj);
	add_to_gfx_buf(gfx, tmp);
}

void	send_hatching_gfx(int sock, t_gfx *gfx)
{
	char	ret[BUFF + 1];

	sprintf(ret, "pfk #%d\n", sock);
	add_to_gfx_buf(gfx, ret);
}

void	regen_map(t_zaap *zp)
{
	t_stock		*inv;
	int			i;
	int			j;

	i = 0;
	while (i < zp->y)
	{
		j = 0;
		while (j < zp->x)
		{
			inv = zp->map[i][j].ressources;
			if (inv->food == 0)
			{
				inv->food = rand_a_b(1, 11);
				if (zp->gfx)
					send_spot(zp->map[i][j], zp->gfx, i, j);
			}
			j++;
		}
		i++;
	}
	action_time(&(zp->regen), zp->time, 1260 * 10);
}

void	loop_map(t_zaap *zaap)
{
	int					ret;
	struct timeval		tv;

	tv.tv_sec = 0;
	tv.tv_usec = 0;
	action_time(&(zaap->regen), zaap->time, 1260 * 10);
	while (42)
	{
		ret = 0;
		if (make_game(zaap))
			break ;
		if (is_time_yet(zaap->regen))
			regen_map(zaap);
		init_fd(zaap);
		ret = select(zaap->max + 1, &zaap->fd_rd, &zaap->fd_wr, NULL, &tv);
		check_fd(ret, zaap);
	}
}

int		main(int argc, char **argv)
{
	t_zaap		*zaap;

	if (argc < 12)
		zaap_error(-1);
	zaap = get_zaap(argv);
	debug_1(zaap);
	loop_map(zaap);
	exit_zaapy(zaap);
	return (0);
}
