/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_buff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:00:59 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 19:11:38 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "zaap.h"
#include "libft.h"

t_buff			*init_buff(void)
{
	t_buff		*new;

	if ((new = (t_buff *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->buff_wr = NULL;
	new->next = NULL;
	return (new);
}

static void		find_room_buff(t_buff *bws, char *str)
{
	while (bws->next)
		bws = bws->next;
	bws->next = init_buff();
	bws->next->buff_wr = ft_strdup(str);
}

void			add_to_gfx_buf(t_gfx *gfx, char *str)
{
	int			len;

	len = ft_strlen(str);
	gfx->to_send += len;
	if (gfx->list == NULL)
	{
		gfx->list = init_buff();
		gfx->list->buff_wr = ft_strdup(str);
	}
	else
		find_room_buff(gfx->list, str);
}
