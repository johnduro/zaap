/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:28 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/09 22:28:22 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include "zaap.h"
#include "libft.h"

void	init_player_fd(t_player *bwspl, t_zaap *zaap)
{
	while (bwspl)
	{
		FD_SET(bwspl->sock, &zaap->fd_rd);
		if (ft_strlen(bwspl->buff_wr) > 0)
			FD_SET(bwspl->sock, &zaap->fd_wr);
		zaap->max = ft_isgreater(zaap->max, bwspl->sock);
		bwspl = bwspl->next;
	}
}

void	init_fd(t_zaap *zaap)
{
	t_team		*bwst;
	t_temp		*bwstmp;

	zaap->max = zaap->sock;
	FD_ZERO(&zaap->fd_rd);
	FD_ZERO(&zaap->fd_wr);
	FD_SET(zaap->sock, &zaap->fd_rd);
	bwstmp = zaap->wait;
	bwst = zaap->teams;
	while (bwstmp)
	{
		FD_SET(bwstmp->sock, &zaap->fd_rd);
		if (ft_strlen(bwstmp->buf_wr) > 0)
			FD_SET(bwstmp->sock, &zaap->fd_wr);
		zaap->max = ft_isgreater(zaap->max, bwstmp->sock);
		bwstmp = bwstmp->next;
	}
	while (bwst)
	{
		if (bwst->first)
			init_players_fd(bwst->first, zaap);
		bwst = bwst->next;
	}
}

void	check_fd(int ret, t_zaap *zaap)
{
	t_team		*bwst;

	if (ret <= 0)
		return ;
	bwst = zaap->teams;
	if (FD_ISSET(zaap->sock, &zaap->fd_rd))
		accept_client(zaap);//a faire
	check_tmp_fd(zaap->wait, zaap);//a faire
	while (bwst)
	{
		check_players_fd(bwst->first, zaap);//a faire
		bwst = bwst->next;
	}
}

void	loop_map(t_zaap *zaap)
{
	int					ret;
	struct timeval		tv;

	while (42)
	{
		ret = 0;
//		check_actions(zaap); //a faire
		init_fd(zaap);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		ret = select(zaap->max + 1, &zaap->fd_rd, &zaap->fr_wr, NULL, &tv);
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
//	exit_zaapy(zaap);
	return (0);
}
