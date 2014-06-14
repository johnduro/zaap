/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_gfx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/14 18:02:27 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/14 20:13:23 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "zaap.h"
#include "libft.h"

t_player				*get_player(int sock, t_zaap *zaap)
{
	t_team		*bwst;
	t_player	*bwspl;

	bwst = zaap->teams;
	while (bwst)
	{
		if (bwst->first)
		{
			bwspl = bwst->first;
			while (bwspl)
			{
				if (bwspl->sock == sock)
					return (bwspl);
				bwspl = bwspl->next;
			}
		}
		bwst = bwst->next;
	}
	return (NULL);
}

static t_prs			*get_parse_gfx(void)
{
	static t_prs	parse[] =

	{
	{"msz", &gfx_map_size},
	{"bct", &gfx_spot_content},
	{"mct", &gfx_all_map},
	{"tna", &gfx_teams_name},
	{"ppo", &gfx_player_pos},
	{"plv", &gfx_player_lvl},
	{"pin", &gfx_player_inv},
	{"sgt", &gfx_get_time},
	{"sst", &gfx_set_time},
	{NULL, NULL}
	};
	return (parse);
}

static void				check_ret(int ret, t_gfx *gfx)
{
	if (ret == 1)
		add_to_gfx_buf(gfx, "suc\n");
	else if (ret == -1)
		add_to_gfx_buf(gfx, "sbp\n");
}

void					treat_gfx(t_gfx *gfx, t_zaap *zaap)
{
	char		**split;
	t_prs		*parse;
	int			i;
	int			ret;

	ret = 1;
	split = split_n_trim(gfx->buff_rd);
	parse = get_parse_gfx();
	i = 0;
	while (parse[i].name)
	{
		if (!ft_strcmp(parse[i].name, *split))
		{
			ret = parse[i].fn(split, gfx, zaap);
			break ;
		}
		i++;
	}
	check_ret(ret, gfx);
	ft_strclr(gfx->buff_rd);
	ft_tabfree(&split);
}
