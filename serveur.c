/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:28 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/19 18:00:44 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "zaap.h"
#include "libft.h"

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

char	**split_n_trim(char *str)
{
	char	**tab;
	char	*trim;

	trim = ft_strtrim(str);
	tab = ft_strsplit(trim, ' ');
	free(trim);
	return (tab);
}

//int is_time_yet(struct timeval ok);
//void action_time(struct timeval *res, int time, int lenght);

void	add_player_buff(t_player *pl, char *str)
{
	if ((BUFF - (ft_strlen(pl->buff_wr) + ft_strlen(str))) > 1)
		ft_strcat(pl->buff_wr, str);
}

void	send_change(int sock, t_gfx *gfx, char flag, int obj)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_itoa(sock);
	if (flag)
		tmp2 = ft_strjoin("pgt #", tmp);
	else
		tmp2 = ft_strjoin("pdr #", tmp);
	free(tmp);
	tmp = ft_itoa(obj);
	tmp3 = ft_strjoinwsep(tmp2, tmp, ' ');
	free(tmp2);
	free(tmp);
	tmp = ft_strjoin(tmp3, "\n");
	free(tmp3);
	add_to_gfx_buf(gfx, tmp);
	free(tmp);
}

int		make_inv(t_action *act, t_player *pl, t_zaap *zaap)
{
	char		tmp[BUFF + 1];
	char		tmp2[BUFF + 1];
	char		*ret;
	t_stock		*i;

	(void)act;
	(void)zaap;
	i = pl->inventory;
	sprintf(tmp, INV_1, i->food, i->linemate, i->deraumere, i->sibur);
	sprintf(tmp2, INV_2, i->mendiane, i->phiras, i->thystame);
	ret = ft_strjoin(tmp, tmp2);
	add_player_buff(pl, ret);
	free(ret);
	return (0);
}

void    ft_strjoin_free(char **s1, char *s2)
{
    char    *tmp;

    tmp = *s1;
    *s1 = ft_strjoin(tmp, s2);
    ft_strdel(&tmp);
}

int     ft_addnstr(char **s, int bol, int n, char *str)
{
    int     i;
    int     ret;

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
        if (i !=  n)
            ft_strjoin_free(s, " ");
        ret = 1;
    }
    return (ret);
}

int		make_connect(t_action *act, t_player *pl, t_zaap *zaap)
{
	char	*tmp;
	char	*ret;

	(void)act;
	(void)zaap;
	tmp = ft_itoa(pl->p_team->places);
	ret = ft_strjoin(tmp, "\n");
	free(tmp);
	add_player_buff(pl, ret);
	free(ret);
	return (0);
}

void	send_hatching_gfx(int sock, t_gfx *gfx)
{
	char	ret[BUFF + 1];

	sprintf(ret, "pfk #%d\n", sock);
	add_to_gfx_buf(gfx, ret);
}

void	send_failed_elv_gfx(t_player *pl, t_gfx *gfx)
{
	char	tmp[BUFF + 1];

	sprintf(tmp, "pie %d %d 0\n", pl->pos_x, pl->pos_y);
	add_to_gfx_buf(gfx, tmp);
}

void	make_game(t_zaap *zaap)
{
	t_team		*bwst;
	t_player	*bwspl;

	bwst = zaap->teams;
	while (bwst)
	{
//		check_win(bwst, zaap); //a faire
		check_eggs(bwst, zaap);
		bwspl = bwst->first;
		while (bwspl)
		{
			player_game(bwspl, zaap);
			bwspl = bwspl->next;
		}
		bwst = bwst->next;
	}
}

void	loop_map(t_zaap *zaap)
{
	int					ret;
	struct timeval		tv;

	while (42)
	{
		ret = 0;
		make_game(zaap);
		init_fd(zaap);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		ret = select(zaap->max + 1, &zaap->fd_rd, &zaap->fd_wr, NULL, &tv);
		check_fd(ret, zaap);
	}
}

int		main(int argc, char **argv)
{
	t_zaap		*zaap;

	if (argc < 12)
		zaap_error(-1);
	zaap = get_zaap(argv);
	debug_1(zaap);
	loop_map(zaap);
//	exit_zaapy(zaap);
	return (0);
}
