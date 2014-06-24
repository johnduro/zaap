/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 15:25:57 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/12 20:08:14 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "zaap.h"
#include "libft.h"

int					find_read(char *str)
{
	int		ret;

	ret = 0;
	while (*str)
	{
		if (*str == '\n')
			break ;
		str++;
		ret++;
	}
	if (*str == '\0')
		return (-1);
	return (ret);
}

static t_temp		*init_tmp(int sock)
{
	t_temp		*new;

	if ((new = (t_temp *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->sock = sock;
	new->buff_rd[0] = '\0';
	new->buff_wr[0] = '\0';
	ft_strcat(new->buff_wr, "BIENVENUE\n");
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static void			add_tmp(t_temp *tmp, t_zaap *zaap)
{
	t_temp		*bwstmp;

	if (zaap->wait == NULL)
		zaap->wait = tmp;
	else
	{
		bwstmp = zaap->wait;
		while (bwstmp->next)
			bwstmp = bwstmp->next;
		bwstmp->next = tmp;
		tmp->prev = bwstmp;
	}
}

static void			accept_client(t_zaap *zaap)
{
	int						cs;
	int						port;
	struct sockaddr_in		csin;
	socklen_t				csin_len;
	t_temp					*tmp;

	csin_len = sizeof(csin);
	if ((cs = accept(zaap->sock, (struct sockaddr*)&csin, &csin_len)) == -1)
		return ;
	port = ntohs(csin.sin_port);
	printf("New client #%d from %s:%d\n", cs, inet_ntoa(csin.sin_addr), port);
	tmp = init_tmp(cs);
	add_tmp(tmp, zaap);
}

void				check_fd(int ret, t_zaap *zaap)
{
	t_team		*bwst;

	if (ret <= 0)
		return ;
	bwst = zaap->teams;
	if (FD_ISSET(zaap->sock, &zaap->fd_rd))
		accept_client(zaap);
	if (zaap->gfx)
		check_gfx(zaap, zaap->gfx);
	while (bwst)
	{
		check_players_fd(bwst->first, zaap, bwst);
		bwst = bwst->next;
	}
	check_tmp_fd(zaap->wait, zaap);
}
