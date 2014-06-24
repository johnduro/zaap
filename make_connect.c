/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_connect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 21:05:03 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 21:06:00 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

int			make_connect(t_action *act, t_player *pl, t_zaap *zaap)
{
	char		*tmp;
	char		*ret;

	(void)act;
	(void)zaap;
	tmp = ft_itoa(pl->p_team->places);
	ret = ft_strjoin(tmp, "\n");
	free(tmp);
	add_player_buff(pl, ret);
	free(ret);
	return (0);
}
