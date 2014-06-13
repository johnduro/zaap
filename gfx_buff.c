/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_buff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:00:59 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/12 17:38:10 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

static t_buff	*init_buff(void)
{
	t_buff		*new;

	if ((new = (t_buff *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->buff_wr[0] = '\0';
	new->next = NULL;
	return (new);
}

static void		find_room_buff(t_buff *bws, char *str, int len)
{
	t_buff		*keep;

	while (bws)
	{
		if (((BUFF + 1) - (ft_strlen(bws->buff_wr) + len)) > 1)
		{
			ft_strcat(bws->buff_wr, str);
			return ;
		}
		keep = bws;
		bws = bws->next;
	}
	keep->next = init_buff();
	ft_strcat(keep->next->buff_wr, str);
}

void			add_to_gfx_buf(t_gfx *gfx, char *str)
{
	int			len;

	len = ft_strlen(str);
	gfx->to_send += len;
	if (gfx->list == NULL)
	{
		gfx->list = init_buff();
		ft_strcat(gfx->list->buff_wr, str);
	}
	else
		find_room_buff(gfx->list, str, len);
}
