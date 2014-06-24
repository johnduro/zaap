/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_coor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 21:02:58 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 21:03:39 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zaap.h"

int			vd(int coor, int max)
{
	if (coor >= 0 && coor < max)
		return (coor);
	else if (coor < 0)
	{
		while (coor < 0)
			coor += max;
		return (coor);
	}
	else if (coor >= max)
	{
		while (coor >= max)
			coor -= max;
		return (coor);
	}
	return (0);
}
