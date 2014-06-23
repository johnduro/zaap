/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_gfx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 18:30:23 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/23 15:52:39 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

char			*get_inv_gfx(int player, t_zaap *zaap)
{
	char		*tmp;
	char		*tmp2;
	char		*tmp3;
	t_player	*get;

	if ((get = get_player(player, zaap)) == NULL)
		return (NULL);
	tmp = ft_itoa(get->sock);
	tmp2 = ft_strjoin("pin #", tmp);
	free(tmp);
	tmp = pos_n_stock(get->inventory, get->pos_x, get->pos_y);
	tmp3 = ft_strjoinwsep(tmp2, tmp, ' ');
	free(tmp2);
	free(tmp);
	tmp = ft_strjoin(tmp3, "\n");
	free(tmp3);
	return (tmp);
}

int				gfx_player_inv(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	int			player;
	char		*ret;

	if (!tab[1] || (tab[1] && tab[1][0] != '#'))
		return (-1);
	player = ft_atoi(&tab[1][1]);
	if ((ret = get_inv_gfx(player, zaap)) == NULL)
		return (-1);
	add_to_gfx_buf(gfx, ret);
	free(ret);
	return (0);
}

char			*get_lvl_gfx(int sock, t_zaap *zaap)
{
	char		*tmp;
	char		*tmp2;
	char		*tmp3;
	t_player	*pl;

	if ((pl = get_player(sock, zaap)) == NULL)
		return (NULL);
	tmp = ft_itoa(pl->sock);
	tmp2 = ft_strjoin("plv #", tmp);
	free(tmp);
	tmp = ft_itoa(pl->lvl);
	tmp3 = ft_strjoinwsep(tmp2, tmp, ' ');
	free(tmp);
	free(tmp2);
	tmp = ft_strjoin(tmp3, "\n");
	free(tmp3);
	return (tmp);
}

int				gfx_player_lvl(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	int			player;
	char		*ret;

	if (!tab[1] || (tab[1] && tab[1][0] != '#'))
		return (-1);
	player = ft_atoi(&tab[1][1]);
	if ((ret = get_lvl_gfx(player, zaap)) == NULL)
		return (-1);
	add_to_gfx_buf(gfx, ret);
	free(ret);
	return (0);
}

int				gfx_player_pos(char **tab, t_gfx *gfx, t_zaap *zaap)
{
	int				player;
	t_player		*pl;

	if (!tab[1] || (tab[1] && tab[1][0] != '#'))
		return (-1);
	player = ft_atoi(&tab[1][1]);
	if ((pl = get_player(player, zaap)) == NULL)
		return (-1);
	get_pos_player_gfx(pl, gfx);
	return (0);
}
