/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/12 16:41:27 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/12 19:52:18 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "zaap.h"

static void			place_player_rand(t_player *new, t_zaap *zaap)
{
	new->pos_x = rand_a_b(0, zaap->x);
	new->pos_y = rand_a_b(0, zaap->y);
	add_player_to_map(new, zaap);
}

static t_player		*init_player(int sock)
{
	t_player		*new;

	if ((new = (t_player *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->sock = sock;
	new->pos_x = 0;
	new->pos_y = 0;
	new->dir = rand_a_b(1, 5);
	new->lvl = 1;
	new->inventory = get_inv();
	new->inventory->food = START_FOOD;
	new->a_first = NULL;
	new->a_last = NULL;
	new->buff_wr[0] = '\0';
	new->buff_rd[0] = '\0';
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_team				*check_teams(char *str, t_team *bwst)
{
	char	*trim;

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

static void			set_new_msg(t_player *pl, t_zaap *zaap, t_team *team)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*ret;

	team->places--;
	tmp = ft_itoa(team->places);
	tmp2 = ft_strjoin(tmp, "\n");
	free(tmp);
	tmp = ft_itoa(zaap->x);
	tmp3 = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(tmp2);
	tmp = ft_itoa(zaap->y);
	tmp2 = ft_strjoinwsep(tmp3, tmp, ' ');
	free(tmp3);
	free(tmp);
	ret = ft_strjoin(tmp2, "\n");
	ft_strcat(pl->buff_wr, ret);
	free(tmp2);
	free(ret);
}

void				add_new_client(t_team *team, int sock, t_zaap *zaap)
{
	t_player		*bwspl;
	t_player		*new;
	t_egg			*egg;

	if (team->places <= 0)
	{
		close(sock);
		return ;
	}
	new = init_player(sock);
	set_new_msg(new, zaap, team);
	if (team->first == NULL)
		team->first = new;
	else
	{
		bwspl = team->first;
		while (bwspl->next)
			bwspl = bwspl->next;
		bwspl->next = new;
		new->prev = bwspl;
	}
	if ((egg = egg_rdy(team->eggs)) != NULL)
		place_player_in_egg(team, new, egg, zaap);
	else
		place_player_rand(new, zaap);
}
