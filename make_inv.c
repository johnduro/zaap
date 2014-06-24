/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_inv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:58:31 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:59:57 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

int			make_inv(t_action *act, t_player *pl, t_zaap *zaap)
{
	char		tmp[BUFF + 1];
	char		tmp2[BUFF + 1];
	char		*ret;
	t_stock		*i;

	(void)act;
	(void)zaap;
	i = pl->inventory;
	sprintf(tmp, INV_1, i->food, i->linemate, i->deraumere, i->sibur);
	sprintf(tmp2, INV_2, i->mendiane, i->phiras, i->thystame);
	ret = ft_strjoin(tmp, tmp2);
	add_player_buff(pl, ret);
	free(ret);
	return (0);
}
