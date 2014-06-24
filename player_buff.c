/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_buff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 21:01:32 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 21:02:34 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

void		add_player_buff(t_player *pl, char *str)
{
	int			len;
	t_buff		*bwsb;

	len = ft_strlen(str);
	pl->to_send += len;
	if (pl->list == NULL)
	{
		pl->list = init_buff();
		pl->list->buff_wr = ft_strdup(str);
	}
	else
	{
		bwsb = pl->list;
		while (bwsb->next)
			bwsb = bwsb->next;
		bwsb->next = init_buff();
		bwsb->next->buff_wr = ft_strdup(str);
	}
}
