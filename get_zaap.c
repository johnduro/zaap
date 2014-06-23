/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_zaap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:10:01 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 19:59:04 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <time.h>
#include "zaap.h"
#include "libft.h"

t_stock			*get_inv(void)
{
	t_stock		*new;

	if ((new = (t_stock *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->food = 0;
	new->linemate = 0;
	new->deraumere = 0;
	new->sibur = 0;
	new->mendiane = 0;
	new->phiras = 0;
	new->thystame = 0;
	return (new);
}

int				rand_a_b(int a, int b)
{
	return (random() % (b - a) + a);
}

static void		get_sock(t_zaap *zaap, int port)
{
	struct sockaddr_in		sin;
	struct protoent			*pe;

	if (port < 1024)
		zaap_error(-5);
	pe = getprotobyname("tcp");
	zaap->sock = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (zaap->sock == -1)
		zaap_error(-6);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	if ((bind(zaap->sock, (struct sockaddr*)&sin, sizeof(sin))) == -1)
		zaap_error(-7);
	listen(zaap->sock, 42);
}

static void		init_zaap(t_zaap *zaap)
{
	zaap->sock = -1;
	zaap->x = -1;
	zaap->y = -1;
	zaap->max = -1;
	zaap->nb_start = -1;
	zaap->time = -1;
	zaap->map = NULL;
	zaap->wait = NULL;
	zaap->teams = NULL;
	zaap->gfx = NULL;
	zaap->inc = NULL;
}

t_zaap			*get_zaap(char **arg)
{
	t_zaap		*new;
	int			port;

	port = -1;
	if ((new = (t_zaap *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	init_zaap(new);
	port = get_arg(new, arg);
	get_map(new);
	get_sock(new, port);
	return (new);
}
