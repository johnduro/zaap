/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/11 16:10:13 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/12 19:30:06 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

static void		add_team(t_zaap *zaap, char *name)
{
	t_team	*new;
	t_team	*bwst;

	if ((new = (t_team *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	ft_strcpy(new->name, name);
	new->player_nb = 0;
	new->first = NULL;
	new->eggs = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (zaap->teams == NULL)
		zaap->teams = new;
	else
	{
		bwst = zaap->teams;
		while (bwst->next)
			bwst = bwst->next;
		bwst->next = new;
		new->prev = bwst;
	}
}

static void		get_teams(t_zaap *zaap, char **arg, int i)
{
	int		ret;

	ret = i;
	while (arg[i] && arg[i][0] != '-')
	{
		if (ft_strlen(arg[i]) > BUFF_NAME)
			zaap_error(-3);
		else
			add_team(zaap, arg[i]);
		i++;
	}
	if (i == ret)
		zaap_error(-1);
}

void			add_teams_nb(t_team *bwst, int nb)
{
	while (bwst)
	{
		bwst->places = nb;
		bwst = bwst->next;
	}
}

int				get_arg(t_zaap *zaap, char **arg)
{
	int		i;
	int		port;

	i = 0;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "-x") && arg[i + 1])
			zaap->x = ft_atoi(arg[i + 1]);
		else if (!ft_strcmp(arg[i], "-p") && arg[i + 1])
			port = ft_atoi(arg[i + 1]);
		else if (!ft_strcmp(arg[i], "-y") && arg[i + 1])
			zaap->y = ft_atoi(arg[i + 1]);
		else if (!ft_strcmp(arg[i], "-n") && arg[i + 1])
			get_teams(zaap, arg, i + 1);
		else if (!ft_strcmp(arg[i], "-c") && arg[i + 1])
			zaap->nb_start = ft_atoi(arg[i + 1]);
		else if (!ft_strcmp(arg[i], "-t") && arg[i + 1])
			zaap->time = ft_atoi(arg[i + 1]);
		i++;
	}
	if (zaap->teams)
		add_teams_nb(zaap->teams, zaap->nb_start);
	else
		zaap_error(-1);
	return (port);
}
