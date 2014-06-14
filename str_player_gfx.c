/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_player_gfx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 19:02:09 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/14 19:11:57 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

static char		*pos_n_dir(t_player *pl)
{
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	tmp = get_pos(pl->pos_x, pl->pos_y);
	tmp2 = ft_itoa(pl->dir);
	tmp3 = ft_strjoinwsep(tmp, tmp2, ' ');
	free(tmp);
	free(tmp2);
	return (tmp3);
}

void			get_pos_player_gfx(t_player *pl, t_gfx *gfx)
{
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	tmp = ft_itoa(pl->sock);
	tmp2 = ft_strjoin("ppo #", tmp);
	free(tmp);
	tmp3 = pos_n_dir(pl);
	tmp = ft_strjoinwsep(tmp2, tmp3, ' ');
	free(tmp2);
	free(tmp3);
	tmp2 = ft_strjoin(tmp, "\n");
	free(tmp);
	add_to_gfx_buf(gfx, tmp2);
	free(tmp2);
}

static char		*new_player_gfx(t_player *pl)
{
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	tmp = ft_itoa(pl->sock);
	tmp2 = ft_strjoin("pnw #", tmp);
	free(tmp);
	tmp3 = pos_n_dir(pl);
	tmp = ft_strjoinwsep(tmp2, tmp3, ' ');
	free(tmp2);
	free(tmp3);
	return (tmp);
}

void			send_new_player(t_player *pl, t_gfx *gfx, t_team *team)
{
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	tmp = new_player_gfx(pl);
	tmp2 = ft_itoa(pl->lvl);
	tmp3 = ft_strjoinwsep(tmp, tmp2, ' ');
	free(tmp);
	free(tmp2);
	tmp = ft_strjoinwsep(tmp3, team->name, ' ');
	free(tmp3);
	tmp2 = ft_strjoin(tmp, "\n");
	free(tmp);
	add_to_gfx_buf(gfx, tmp2);
	free(tmp2);
}
