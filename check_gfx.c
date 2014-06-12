/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gfx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 15:36:38 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/12 16:13:43 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

static void		remove_gfx_buff(t_gfx *gfx)
{
	t_buff		*bwsbuf;
	t_buff		*keep;

	gfx->to_send = 0;
	bwsbuf = gfx->list;
	while (bwsbuf)
	{
		keep = bwsbuf->next;
		free(bwsbuf);
		bwsbuf = keep;
	}
	gfx->list = NULL;
}

static void		write_to_gfx(t_gfx *gfx)
{
	char		*to_send;
	t_buff		*bwsbuf;

	bwsbuf = gfx->list;
	to_send = ft_strnew(gfx->to_send);
	while (bwsbuf)
	{
		ft_strcat(to_send, bwsbuf->buff_wr);
		bwsbuf = bwsbuf->next;
	}
	send(gfx->sock, to_send, gfx->to_send, 0);//retour ?
	remove_gfx_buff(gfx);
}

static void		remove_gfx(t_zaap *zaap)
{
	remove_gfx_buff(zaap->gfx);
	free(zaap->gfx);
	zaap->gfx = NULL;
}

static void		read_gfx(t_gfx *gfx, t_zaap *zaap)
{
	int		ret;
	int		read;

	read = -1;
	if ((ret = recv(gfx->sock, gfx->buff_rd, BUFF, MSG_PEEK)) > 0)
	{
		gfx->buff_rd[ret] = '\0';
		read = find_read(gfx->buff_rd);
		if (read > -1)
		{
			ret = recv(gfx->sock, gfx->buff_rd, read + 1, 0);
			if (ret <= 0)
			{
				remove_gfx(zaap);
				return ;
			}
			gfx->buff_rd[ret] = '\0';
			printf("GFX said: %s", gfx->buff_rd);
			treat_gfx(gfx, zaap);
		}
	}
	else if (ret <= 0)
		remove_gfx(zaap);
}

void			check_gfx(t_zaap *zaap, t_gfx *gfx)
{
	if (zaap->gfx)
	{
		if (FD_ISSET(gfx->sock, &zaap->fd_wr))
			write_to_gfx(gfx);
		else if (FD_ISSET(gfx->sock, &zaap->fd_rd))
			read_gfx(gfx, zaap);
	}
}
