/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:11:37 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/25 16:38:44 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

void			remove_player_buf(t_player *pl)
{
	t_buff		*bwsbuf;
	t_buff		*keep;

	pl->to_send = 0;
	bwsbuf = pl->list;
	while (bwsbuf)
	{
		keep = bwsbuf->next;
		if (bwsbuf->buff_wr)
			free(bwsbuf->buff_wr);
		free(bwsbuf);
		bwsbuf = keep;
	}
	pl->list = NULL;
}

static void		write_player(t_player *player, t_zaap *zaap, t_team *team)
{
	char	*to_send;
	char	*tmp;
	t_buff	*bwsbuf;

	bwsbuf = player->list;
	to_send = ft_strnew(0);
	while (bwsbuf)
	{
		tmp = ft_strjoin(to_send, bwsbuf->buff_wr);
		free(to_send);
		to_send = tmp;
		bwsbuf = bwsbuf->next;
	}
	if ((send(player->sock, to_send, player->to_send, 0)) == -1)
		zaap_error(-8);
	printf("sending to player: %d\n-->%s", player->sock, to_send);
	free(to_send);
	remove_player_buf(player);
	if (!(player->alive))
		remove_pl(player, team, zaap);
}

static void		read_player(t_player *pl, t_zaap *zaap, t_team *t)
{
	int		ret;
	int		read;

	read = -1;
	if ((ret = recv(pl->sock, pl->buff_rd, BUFF, MSG_PEEK)) > 0)
	{
		pl->buff_rd[ret] = '\0';
		read = find_read(pl->buff_rd);
		if (read > -1)
		{
			ret = recv(pl->sock, pl->buff_rd, read + 1, 0);
			if (ret <= 0)
			{
				remove_pl(pl, t, zaap);
				return ;
			}
			pl->buff_rd[ret] = '\0';
			printf(RECV, pl->sock, pl->nba, t->name, pl->buff_rd);
			treat_player(pl, zaap);
		}
	}
	else if (ret <= 0)
		remove_pl(pl, t, zaap);
}

void			check_players_fd(t_player *bwspl, t_zaap *zaap, t_team *team)
{
	t_player	*keep;

	while (bwspl)
	{
		keep = bwspl->next;
		if (FD_ISSET(bwspl->sock, &zaap->fd_wr))
			write_player(bwspl, zaap, team);
		else if (FD_ISSET(bwspl->sock, &zaap->fd_rd))
			read_player(bwspl, zaap, team);
		bwspl = keep;
	}
}
