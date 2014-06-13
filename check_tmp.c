/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:19:36 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/13 16:11:58 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

static void			write_tmp(t_temp *tmp)
{
	send(tmp->sock, tmp->buff_wr, ft_strlen(tmp->buff_wr), 0);
	ft_strclr(tmp->buff_wr);
}

void				remove_tmp(t_temp *tmp, t_zaap *zaap, int flag)
{
	if (flag)
		close(tmp->sock);
	if (tmp->prev == NULL && tmp->next == NULL)
		zaap->wait = NULL;
	else if (tmp->prev && tmp->next == NULL)
		tmp->prev->next = NULL;
	else if (tmp->prev == NULL && tmp->next)
	{
		zaap->wait = tmp->next;
		tmp->next->prev = NULL;
	}
	else if (tmp->prev && tmp->next)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	free(tmp);
}

static void			treat_tmp(t_temp *tmp, t_zaap *zaap)
{
	t_team		*team;

	if (!ft_strcmp(tmp->buff_rd, "GRAPHIC\n"))
	{
		if (zaap->gfx)
			ft_strcat(tmp->buff_wr, "There is already a gfx client\n");
		else
		{
			zaap->gfx = init_gfx(tmp->sock, zaap);
			remove_tmp(tmp, zaap, 0);
		}
	}
	else if ((team = check_teams(tmp->buff_rd, zaap->teams)) != NULL)
	{
		add_new_client(team, tmp->sock, zaap);
		remove_tmp(tmp, zaap, 0);
	}
	else
		ft_strcat(tmp->buff_wr, "I don't understand you...\n");
}

static void			read_tmp(t_temp *tmp, t_zaap *zaap)
{
	int		ret;
	int		read;

	read = -1;
	if ((ret = recv(tmp->sock, tmp->buff_rd, BUFF, MSG_PEEK)) > 0)
	{
		tmp->buff_rd[ret] = '\0';
		read = find_read(tmp->buff_rd);
		if (read > -1)
		{
			ret = recv(tmp->sock, tmp->buff_rd, read + 1, 0);
			if (ret <= 0)
			{
				remove_tmp(tmp, zaap, -1);
				return ;
			}
			tmp->buff_rd[ret] = '\0';
			printf("Receive from %d: %s", tmp->sock, tmp->buff_rd);
			treat_tmp(tmp, zaap);
		}
	}
	else if (ret <= 0)
		remove_tmp(tmp, zaap, -1);
}

void				check_tmp_fd(t_temp *bwstmp, t_zaap *zaap)
{
	t_temp		*keep;

	while (bwstmp)
	{
		keep = bwstmp->next;
		if (FD_ISSET(bwstmp->sock, &zaap->fd_wr))
			write_tmp(bwstmp);
		else if (FD_ISSET(bwstmp->sock, &zaap->fd_rd))
			read_tmp(bwstmp, zaap);
		bwstmp = keep;
	}
}
