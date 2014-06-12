/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:11:37 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/12 20:08:25 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

static void		free_actions(t_action *list)
{
	t_action	*keep;

	while (list)
	{
		keep = list->next;
		free(list);
		list = keep;
	}
}

void			remove_pl(t_player *pl, t_team *team)
{
	close(pl->sock);
	if (pl->prev == NULL && pl->next == NULL)
		team->first = NULL;
	else if (pl->prev && pl->next == NULL)
		pl->prev->next = NULL;
	else if (pl->prev == NULL && pl->next)
	{
		team->first = pl->next;
		pl->next->prev = NULL;
	}
	else if (pl->prev && pl->next)
	{
		pl->prev->next = pl->next;
		pl->next->prev = pl->prev;
	}
	if (pl->inventory)
		free(pl->inventory);
	if (pl->a_first)
		free_actions(pl->a_first);
	free(pl);
}

static void		write_player(t_player *player)
{
	send(player->sock, player->buff_wr, ft_strlen(player->buff_wr), 0);
	ft_strclr(player->buff_wr);
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
				remove_pl(pl, t);
				return ;
			}
			pl->buff_rd[ret] = '\0';
			printf("Player %d in team %s: %s", pl->sock, t->name, pl->buff_rd);
			treat_player(pl, zaap);
		}
	}
	else if (ret <= 0)
		remove_pl(pl, t);
}

void			check_players_fd(t_player *bwspl, t_zaap *zaap, t_team *team)
{
	while (bwspl)
	{
		if (FD_ISSET(bwspl->sock, &zaap->fd_wr))
			write_player(bwspl);
		else if (FD_ISSET(bwspl->sock, &zaap->fd_rd))
			read_player(bwspl, zaap, team);
		bwspl = bwspl->next;
	}
}
