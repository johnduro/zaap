/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_serv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:48:51 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/12 17:10:01 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

t_caps		*init_caps(t_player *player, t_egg *egg)
{
	t_caps		*new;

	if ((new = (t_caps *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->player = NULL;
	new->egg = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (player)
		new->player = player;
	else if (egg)
		new->egg = egg;
	return (new);
}

t_gfx		*init_gfx(int sock)
{
	t_gfx		*new;

	if ((new = (t_gfx *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->sock = sock;
	new->to_send = 0;
	new->list = NULL;
	return (new);
}
