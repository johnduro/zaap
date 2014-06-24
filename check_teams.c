/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_teams.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 20:00:57 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 20:01:57 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

t_team			*check_teams(char *str, t_team *bwst)
{
	char		*trim;

	trim = ft_strtrim(str);
	while (bwst)
	{
		if (!ft_strcmp(trim, bwst->name))
		{
			free(trim);
			return (bwst);
		}
		bwst = bwst->next;
	}
	free(trim);
	return (NULL);
}
