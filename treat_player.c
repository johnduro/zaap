/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 17:35:22 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/16 20:45:41 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

t_action	*init_action(int type, char *str, int lenght)
{
	t_action	*new;

	if ((new = (t_action *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->type = type;
	if (str && *str != '\0')
		ft_strcat(new->buff, str);
	new->lenght = lenght;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		add_action_player(t_action *act, t_player *pl, t_zaap *zp)
{
	(pl->nba)++;
	if (pl->a_first == NULL)
	{
		pl->a_first = act;
		pl->a_last = act;
		action_time(&(act->finish), zp->time, act->lenght);
	}
	else
	{
		pl->a_last->next = act;
		act->prev = pl->a_last;
		pl->a_last = act;
	}
}

t_ply		*get_parse_play(void)
{
	static t_ply	parse[] =

	{
	{"avance", &player_go},
	{"droite", &player_right},
	{"gauche", &player_left},
	{"voir", &player_see},
	{"inventaire", &player_inv},
	{"prend", &player_take},
	{"pose", &player_drop},
	{"expulse", &player_expulse},
	{"broadcast", &player_broadcast},
	{"incantation", &player_incant},
	{"fork", &player_fork},
	{"connect_nbr", &player_connect},
	{NULL, NULL}
	};
	return (parse);
}

void		treat_player(t_player *pl, t_zaap *zaap)
{
	char		**split;
	t_ply		*parse;
	int			i;
	int			ret; //besoin ?

	i = 0;
	ret = 1;
	split = split_n_trim(pl->buff_rd);
	parse = get_parse_play();
	while (parse[i].name)
	{
		if (!ft_strcmp(parse[i].name, *split))
		{
			ret = parse[i].fn(split, pl, zaap);
			break ;
		}
		i++;
	}
	(void)ret;
//check_player_ret(ret, pl);
	ft_strclr(pl->buff_rd);
	ft_tabfree(&split);
}
