/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_caps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:38:15 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:39:59 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

void		remove_dat_caps(t_caps *bwscps, t_egg *egg, t_zaap *zaap)
{
	if (bwscps->prev == NULL && bwscps->next == NULL)
		zaap->map[egg->y][egg->x].list = NULL;
	else if (bwscps->prev == NULL && bwscps->next)
	{
		zaap->map[egg->y][egg->x].list = bwscps->next;
		bwscps->next->prev = NULL;
	}
	else if (bwscps->prev && bwscps->next)
	{
		bwscps->next->prev = bwscps->prev;
		bwscps->prev->next = bwscps->next;
	}
	else if (bwscps->prev && bwscps->next == NULL)
		bwscps->prev->next = NULL;
	free(bwscps);
}
