/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zaap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/24 21:06:29 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/24 21:08:59 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

char		**split_n_trim(char *str)
{
	char	**tab;
	char	*trim;

	trim = ft_strtrim(str);
	tab = ft_strsplit(trim, ' ');
	free(trim);
	return (tab);
}

void		ft_strjoin_free(char **s1, char *s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = ft_strjoin(tmp, s2);
	ft_strdel(&tmp);
}

int			ft_addnstr(char **s, int bol, int n, char *str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (bol && n)
		ft_strjoin_free(s, " ");
	else if (bol)
		ret = 1;
	while (i < n)
	{
		ft_strjoin_free(s, str);
		i++;
		if (i != n)
			ft_strjoin_free(s, " ");
		ret = 1;
	}
	return (ret);
}
