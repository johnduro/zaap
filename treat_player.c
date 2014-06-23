/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/16 17:35:22 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 16:30:32 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
	{
		bzero(new->buff, BUFF);
		ft_strcat(new->buff, str);
	}
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
		if (act->type == FRK && zp->gfx)
			send_hatching_gfx(pl->sock, zp->gfx);
		else if (act->type == ELV)
			start_elev(act, pl, zp);
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

void		end_treat(t_player *pl, int ret)
{
	ft_strclr(pl->buff_rd);
	if (ret)
		add_player_buff(pl, "ko\n");
}

void		treat_player(t_player *pl, t_zaap *zaap)
{
	char		**split;
	t_ply		*parse;
	int			i;
	int			ret;

	i = 0;
	ret = 1;
	if (pl->buff_rd[0] == '\n')
	{
		ft_strclr(pl->buff_rd);
		return ;
	}
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
	end_treat(pl, ret);
	ft_tabfree(&split);
}
