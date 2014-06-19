/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:28 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/17 22:33:46 by mle-roy          ###   ########.fr       */
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

int		check_food(t_player *pl, t_zaap *zaap)
{
	char	ret[BUFF + 1];

	if (is_time_yet(pl->tick))
	{
		(pl->inventory->food)--;
		if (pl->inventory->food <= 0)
		{
			pl->alive = 0;
			add_player_buff(pl, "mort\n");
			sprintf(ret, "pdi #%d\n", pl->sock);
			add_to_gfx_buf(zaap->gfx, ret);
			return (-1);
		}
		else
			action_time(&(pl->tick), zaap->time, 126);
	}
	return (0);
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

t_egg	*init_egg(int x, int y, int time)
{
	t_egg			*new;
	static int		nb = 1;

	if ((new = (t_egg *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->ok = 0;
	new->x = x;
	new->y = y;
	new->nb = nb;
	new->next = NULL;
	new->prev = NULL;
	action_time(&(new->hatch), time, 600);
	nb++;
	return (new);
}

void	add_caps_map(t_caps *caps, int x, int y, t_zaap *zaap)
{
	t_caps	*bwscps;

	bwscps = zaap->map[y][x].list;
	if (bwscps == NULL)
		zaap->map[y][x].list = caps;
	else
	{
		while (bwscps->next)
			bwscps = bwscps->next;
		bwscps->next = caps;
		caps->prev = bwscps;
	}
}

void	add_egg_map(t_egg *egg, t_zaap *zaap)
{
	t_caps	*caps;

	caps = init_caps(NULL, egg);
	add_caps_map(caps, egg->x, egg->y, zaap);
}

void	add_egg_team(t_egg *egg, t_team *team)
{
	t_egg	*bwseg;

	if (team->eggs == NULL)
		team->eggs = egg;
	else
	{
		bwseg = team->eggs;
		while (bwseg->next)
			bwseg = bwseg->next;
		bwseg->next = egg;
		egg->prev = bwseg;
	}
}

int		make_fork(t_action *act, t_player *pl, t_zaap *zaap)
{
	t_egg	*egg;
	char	tmp[BUFF + 1];

	(void)act;
	egg = init_egg(pl->pos_x, pl->pos_y, zaap->time);
	add_egg_team(egg, pl->p_team);
	add_egg_map(egg, zaap);
	if (zaap->gfx)
	{
		sprintf(tmp, "enw #%d #%d %d %d\n", egg->nb, pl->sock, egg->x, egg->y);
		add_to_gfx_buf(zaap->gfx, tmp);
	}
	add_player_buff(pl, "ok\n");
	return (0);
}

void	send_suc_elv_gfx(t_player *pl, t_gfx *gfx)
{
	char	tmp[BUFF + 1];

	sprintf(tmp, "pie %d %d 1\n", pl->pos_x, pl->pos_y);
	add_to_gfx_buf(gfx, tmp);
}

int		make_incant(t_action *act, t_player *pl, t_zaap *zaap)
{
	static struct timeval	ref;
	char					tmp[BUFF + 1];

	if (ref.tv_sec != act->finish.tv_sec || ref.tv_usec != act->finish.tv_usec)
	{
		ref.tv_sec = act->finish.tv_sec;
		ref.tv_usec = act->finish.tv_usec;
		if (zaap->gfx)
			send_suc_elv_gfx(pl, zaap->gfx);
	}
	(pl->lvl)++;
	sprintf(tmp, "niveau actuel : %d\n", pl->lvl);
	add_player_buff(pl, tmp);
	return (0);
}

int		ft_distance_carre(t_player *p1, t_player *p2)
{
	int		ret;
	int		x;
	int		y;

	x = (p1->pos_x - p2->pos_x);
	y = (p1->pos_y - p2->pos_y);
	ret = (x * x) + (y * y);
	return (ret);
}

t_player  ft_find_pos(t_zaap *zaap, t_player *src, int plan)
{
	t_player		pos2;

	pos2.pos_x = src->pos_x;
	pos2.pos_y = src->pos_y;
	if (((plan + 3) % 4) != 0 && plan != 0)
	{
		if (plan < 5)
			pos2.pos_x -= zaap->x;
		else
			pos2.pos_x += zaap->x;
	}
	if (((plan + 1) % 4) != 0 && plan != 0)
	{
		if ((plan % 8) < 3)
			pos2.pos_y -= zaap->y;
		else
			pos2.pos_y += zaap->y;
	}
	return (pos2);
}

int		ft_direction(t_player *src, t_player *dest)
{
	int		ret;
	int		dx;
	int		dy;

	dx = (src->pos_x - dest->pos_x) * (src->pos_x - dest->pos_x);
	dy = (src->pos_y - dest->pos_y) * (src->pos_y - dest->pos_y);
	ret = 1;
	if (dx == dy)
		ret += 1;
	if (src->pos_x < dest->pos_x && (dx > dy || (dx == dy && src->pos_y > dest->pos_y)))
		ret += 2;
	else if (src->pos_y > dest->pos_y && (dx < dy || (dx == dy && src->pos_x > src->pos_x)))
		ret += 4;
	else if (src->pos_x > dest->pos_x && (dx > dy || (dx == dy && src->pos_y < dest->pos_y)))
		ret += 6;
	if (dest->dir == 2)
		ret = ((ret + 1) % 8) + 1;
	else if (dest->dir == 3)
		ret = ((ret + 3) % 8) + 1;
	else if (dest->dir == 4)
		ret = ((ret + 5) % 8) + 1;
	return (ret);
}

int		ft_broadcast(t_zaap *zaap, t_player *src, t_player *dest)
{
	t_player	plan;
	t_player	tmp;
	int		i;
	int		min;
	int		ret;

	if ((min = ft_distance_carre(src, dest)) == 0)
		return (0);
//	plan = 0;
	i = 1;
	while (i <= 8)
	{
		tmp = ft_find_pos(zaap, src, i);
		ret = ft_distance_carre(&tmp, dest);
		if (ret < min)
		{
			min = ret;
			plan = tmp;
		}
		i++;
	}
//	pos2 = ft_find_pos(arg, pos, plan);
	ret = ft_direction(&plan, dest);
	return (ret);
}


void	send_bc_gfx(int sock, char *str, t_gfx *gfx)
{
	char	ret[BUFF + 1];

	sprintf(ret, "pbc #%d %s\n", sock, str);
	add_to_gfx_buf(gfx, ret);
}

int		make_broadcast(t_action *act, t_player *pl, t_zaap *zaap) //pas fait
{
	t_team		*bwst;
	t_player	*bwspl;
	int			ret;
	char		tmp[BUFF + 1];

	bwst = zaap->teams;
	ret = -1;
	while (bwst)
	{
		bwspl = bwst->first;
		while (bwspl)
		{
			if (bwspl != pl)
			{
				ret = ft_broadcast(zaap, pl, bwspl);
				sprintf(tmp, "message %d %s\n", ret, act->buff);
				add_player_buff(bwspl, tmp);
			}
			bwspl = bwspl->next;
		}
		bwst = bwst->next;
	}
	if (zaap->gfx)
		send_bc_gfx(pl->sock,act->buff, zaap->gfx);
	return (0);
}

void	move_player(t_player *pl, t_zaap *zaap)
{
	remove_player_map(pl, zaap);
	if (pl->dir == NORTH)
		pl->pos_y = vd((pl->pos_y + 1), zaap->y);
	else if (pl->dir == EAST)
		pl->pos_x = vd((pl->pos_x + 1), zaap->x);
	else if (pl->dir == SOUTH)
		pl->pos_y = vd((pl->pos_y - 1), zaap->y);
	else if (pl->dir == WEST)
		pl->pos_x = vd((pl->pos_x - 1), zaap->x);
	add_player_to_map(pl, zaap);
	if (zaap->gfx)
		get_pos_player_gfx(pl, zaap->gfx);
}

void	gfx_expulse(int sock, t_gfx *gfx)
{
	char	ret[BUFF + 1];

	sprintf(ret, "pex #%d\n", sock);
	add_to_gfx_buf(gfx, ret);
}

int		make_expulse(t_action *act, t_player *pl, t_zaap *zaap)
{
	t_caps	*bwscps;
	char	flag;

	(void)act;
	flag = 0;
	bwscps = zaap->map[pl->pos_y][pl->pos_x].list;
	gfx_expulse(pl->sock, zaap->gfx);
	while (bwscps)
	{
		if (bwscps->player && (!bwscps->player->a_first
			|| bwscps->player->a_first->type != ELV))
		{
			move_player(bwscps->player, zaap);
			if (zaap->gfx)
				get_pos_player_gfx(bwscps->player, zaap->gfx);
			add_player_buff(bwscps->player, "deplacement 5\n");
			flag = 1;
		}
		bwscps = bwscps->next;
	}
	if (flag)
		add_player_buff(pl, "ok\n");
	else
		add_player_buff(pl, "ko\n");
	return (0);
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

void    ft_addinv(char **s, t_stock *inv)
{
    int     bol;

    bol = 0;
    bol = ft_addnstr(s, bol, inv->food, "nourriture");
    bol = ft_addnstr(s, bol, inv->linemate, "linemate");
    bol = ft_addnstr(s, bol, inv->deraumere, "deraumere");
    bol = ft_addnstr(s, bol, inv->sibur, "sibur");
    bol = ft_addnstr(s, bol, inv->mendiane, "mendiane");
    bol = ft_addnstr(s, bol, inv->phiras, "phiras");
    bol = ft_addnstr(s, bol, inv->thystame, "thystame");
}


char	*spot_player(t_caps *bwscps, int flag)
{
	int		nb;
	char	*ret;

	nb = 0;
	while (bwscps)
	{
		if (bwscps->player)
			nb++;
		bwscps = bwscps->next;
	}
	if (flag == 1)
		nb--;
	if (nb > 0)
	{
		ret = ft_strnew(0);
		ft_addnstr(&ret, 0, nb, "joueur");
		return (ret);
	}
	return (NULL);
}

char	*see_spot(t_map map, int flag)
{
	char	*inv;
	char	*player;
	char	*ret;

	inv = ft_strnew(0);
	ft_addinv(&inv, map.ressources);
	player = spot_player(map.list, flag);
	if (player)
	{
		ret = ft_strjoin(inv, player);
		free(inv);
		free(player);
	}
	else
		return (inv);
	return (ret);
}

char	*line_west(int x, int max, int y, t_zaap *z)
{
	int		i;
	char	flag;
	char	*tmp;
	char	*ret;

	i = 0;
	flag = 1;
	ret = ft_strnew(0);
	while (i < max)
	{
		tmp = see_spot(z->map[y][x], max);
		if (flag)
		{
			ft_strjoin_free(&ret, tmp);
			flag = 0;
		}
		else
			ft_addnstr(&ret, 1, 1, tmp);
		free(tmp);
		i++;
		y = vd(y - 1, z->y);
	}
	ft_strjoin_free(&ret, ", ");
	return (ret);
}

char	*see_west(int x, int y, t_zaap *z, int lvl)
{
	char	*tmp;
	char	*tmp2;
	char	*keep;
	int		max;

	max = 1;
	tmp2 = ft_strnew(0);
	while (lvl >= 0)
	{
		tmp = line_west(x, max, y, z);
		keep = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		tmp2 = keep;
		lvl--;
		y = vd(y + 1, z->y);
		x = vd(x - 1, z->x);
		max += 2;
	}
	return (tmp2);
}

char	*line_east(int x, int max, int y, t_zaap *z)
{
	int		i;
	char	flag;
	char	*tmp;
	char	*ret;

	i = 0;
	flag = 1;
	ret = ft_strnew(0);
	while (i < max)
	{
		tmp = see_spot(z->map[y][x], max);
		if (flag)
		{
			ft_strjoin_free(&ret, tmp);
			flag = 0;
		}
		else
			ft_addnstr(&ret, 1, 1, tmp);
		free(tmp);
		i++;
		y = vd(y + 1, z->y);
	}
	ft_strjoin_free(&ret, ", ");
	return (ret);
}

char	*see_east(int x, int y, t_zaap *z, int lvl)
{
	char	*tmp;
	char	*tmp2;
	char	*keep;
	int		max;

	max = 1;
	tmp2 = ft_strnew(0);
	while (lvl >= 0)
	{
		tmp = line_east(x, max, y, z);
		keep = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		tmp2 = keep;
		lvl--;
		y = vd(y - 1, z->y);
		x = vd(x + 1, z->x);
		max += 2;
	}
	return (tmp2);
}

char	*line_north(int x, int max, int y, t_zaap *z)
{
	int		i;
	char	flag;
	char	*tmp;
	char	*ret;

	i = 0;
	flag = 1;
	ret = ft_strnew(0);
	while (i < max)
	{
		tmp = see_spot(z->map[y][x], max);
		if (flag)
		{
			ft_strjoin_free(&ret, tmp);
			flag = 0;
		}
		else
			ft_addnstr(&ret, 1, 1, tmp);
		free(tmp);
		i++;
		x = vd(x + 1, z->x);
	}
	ft_strjoin_free(&ret, ", ");
	return (ret);
}

char	*see_north(int x, int y, t_zaap *z, int lvl)
{
	char	*tmp;
	char	*tmp2;
	char	*keep;
	int		max;

	max = 1;
	tmp2 = ft_strnew(0);
	while (lvl >= 0)
	{
		tmp = line_north(x, max, y, z);
		keep = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		tmp2 = keep;
		lvl--;
		y = vd(y - 1, z->y);
		x = vd(x - 1, z->x);
		max += 2;
	}
	return (tmp2);
}

char	*line_south(int x, int max, int y, t_zaap *z)
{
	int		i;
	char	flag;
	char	*tmp;
	char	*ret;

	i = 0;
	flag = 1;
	ret = ft_strnew(0);
	while (i < max)
	{
		tmp = see_spot(z->map[y][x], max);
		if (flag)
		{
			ft_strjoin_free(&ret, tmp);
			flag = 0;
		}
		else
			ft_addnstr(&ret, 1, 1, tmp);
		free(tmp);
		i++;
		x = vd(x - 1, z->x);
	}
	ft_strjoin_free(&ret, ", ");
	return (ret);
}

char	*see_south(int x, int y, t_zaap *z, int lvl)
{
	char	*tmp;
	char	*tmp2;
	char	*keep;
	int		max;

	max = 1;
	tmp2 = ft_strnew(0);
	while (lvl >= 0)
	{
		tmp = line_south(x, max, y, z);
		keep = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
		tmp2 = keep;
		lvl--;
		y = vd(y + 1, z->y);
		x = vd(x + 1, z->x);
		max += 2;
	}
	return (tmp2);
}

int		make_see(t_action *act, t_player *pl, t_zaap *zaap)
{
	char	ret[BUFF + 1];
	char	*all;

	(void)act;
	if (pl->dir == SOUTH)
		all = see_south(pl->pos_x, pl->pos_y, zaap, pl->lvl);
	else if (pl->dir == NORTH)
		all = see_north(pl->pos_x, pl->pos_y, zaap, pl->lvl);
	else if (pl->dir == EAST)
		all = see_east(pl->pos_x, pl->pos_y, zaap, pl->lvl);
	else if (pl->dir == WEST)
		all = see_west(pl->pos_x, pl->pos_y, zaap, pl->lvl);
	all[(ft_strlen(all) - 2)] = '\0';
	sprintf(ret, "{%s}\n", all);
	free(all);
	add_player_buff(pl, ret);
	return (0);
}

int		change_thystame(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->thystame <= 0)
			return (-1);
		(map->thystame)--;
		(inv->thystame)++;
	}
	else
	{
		if (inv->thystame <= 0)
			return (-1);
		(map->thystame)++;
		(inv->thystame)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, FOD);
	return (0);
}

int		change_phiras(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->phiras <= 0)
			return (-1);
		(map->phiras)--;
		(inv->phiras)++;
	}
	else
	{
		if (inv->phiras <= 0)
			return (-1);
		(map->phiras)++;
		(inv->phiras)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, FOD);
	return (0);
}

int		change_mendiane(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->mendiane <= 0)
			return (-1);
		(map->mendiane)--;
		(inv->mendiane)++;
	}
	else
	{
		if (inv->mendiane <= 0)
			return (-1);
		(map->mendiane)++;
		(inv->mendiane)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, FOD);
	return (0);
}

int		change_sibur(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->sibur <= 0)
			return (-1);
		(map->sibur)--;
		(inv->sibur)++;
	}
	else
	{
		if (inv->sibur <= 0)
			return (-1);
		(map->sibur)++;
		(inv->sibur)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, FOD);
	return (0);
}

int		change_deraumere(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->deraumere <= 0)
			return (-1);
		(map->deraumere)--;
		(inv->deraumere)++;
	}
	else
	{
		if (inv->deraumere <= 0)
			return (-1);
		(map->deraumere)++;
		(inv->deraumere)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, FOD);
	return (0);
}

int		change_linemate(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->linemate <= 0)
			return (-1);
		(map->linemate)--;
		(inv->linemate)++;
	}
	else
	{
		if (inv->linemate <= 0)
			return (-1);
		(map->linemate)++;
		(inv->linemate)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, FOD);
	return (0);
}

int		change_food(t_player *pl, t_zaap *zaap, char flag)
{
	t_stock		*map;
	t_stock		*inv;

	map = zaap->map[pl->pos_y][pl->pos_x].ressources;
	inv = pl->inventory;
	if (flag)
	{
		if (map->food <= 0)
			return (-1);
		(map->food)--;
		(inv->food)++;
	}
	else
	{
		if (inv->food <= 0)
			return (-1);
		(map->food)++;
		(inv->food)--;
	}
	if (zaap->gfx)
		send_change(pl->sock, zaap->gfx, flag, FOD);
	return (0);
}

int		obj_use(char *str, t_player *pl, t_zaap *zaap, char flag)
{
	if (!ft_strcmp(str, "food"))
		return (change_food(pl, zaap, flag));
	else if (!ft_strcmp(str, "linemate"))
		return (change_linemate(pl, zaap, flag));
	else if (!ft_strcmp(str, "deraumere"))
		return (change_deraumere(pl, zaap, flag));
	else if (!ft_strcmp(str, "sibur"))
		return (change_sibur(pl, zaap, flag));
	else if (!ft_strcmp(str, "mendiane"))
		return (change_mendiane(pl, zaap, flag));
	else if (!ft_strcmp(str, "phiras"))
		return (change_phiras(pl, zaap, flag));
	else if (!ft_strcmp(str, "thystame"))
		return (change_thystame(pl, zaap, flag));
	return (0);
}

int		make_drop(t_action *act, t_player *pl, t_zaap *zaap)
{
	int		ret;

	ret = -1;
	ret = obj_use(act->buff, pl, zaap, 0);
	if (ret)
		add_player_buff(pl, "ko\n");
	else
		add_player_buff(pl, "ok\n");
	return (0);
}

int		make_take(t_action *act, t_player *pl, t_zaap *zaap)
{
	int		ret;

	ret = -1;
	ret = obj_use(act->buff, pl, zaap, 1);
	if (ret)
		add_player_buff(pl, "ko\n");
	else
		add_player_buff(pl, "ok\n");
	return (0);
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

int		make_left(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	if (pl->dir == NORTH)
		pl->dir = WEST;
	else if (pl->dir == EAST)
		pl->dir = NORTH;
	else if (pl->dir == SOUTH)
		pl->dir = EAST;
	else if (pl->dir == WEST)
		pl->dir = SOUTH;
	if (zaap->gfx)
		get_pos_player_gfx(pl, zaap->gfx);
	add_player_buff(pl, "ok\n");
	return (0);
}

int		make_right(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	if (pl->dir == NORTH)
		pl->dir = EAST;
	else if (pl->dir == EAST)
		pl->dir = SOUTH;
	else if (pl->dir == SOUTH)
		pl->dir = WEST;
	else if (pl->dir == WEST)
		pl->dir = NORTH;
	if (zaap->gfx)
		get_pos_player_gfx(pl, zaap->gfx);
	add_player_buff(pl, "ok\n");
	return (0);
}

int		make_go(t_action *act, t_player *pl, t_zaap *zaap)
{
	(void)act;
	move_player(pl, zaap);
	add_player_buff(pl, "ok\n");
	return (0);
}

t_pac	*get_parse_make(void)
{
	static t_pac	parse[] =

	{
	{AVC, &make_go},
	{DRT, &make_right},
	{GAU, &make_left},
	{SEE, &make_see},
	{INV, &make_inv},
	{TAK, &make_take},
	{PUT, &make_drop},
	{EXP, &make_expulse},
	{BRD, &make_broadcast},
	{ELV, &make_incant},
	{FRK, &make_fork},
	{CNN, &make_connect},
	{0, NULL}
	};
	return (parse);
}

void	send_hatching_gfx(int sock, t_gfx *gfx)
{
	char	ret[BUFF + 1];

	sprintf(ret, "pfk #%d\n", sock);
	add_to_gfx_buf(gfx, ret);
}

void	add_action_front(t_action *act, t_player *pl)
{
	t_action	*cpy;

	cpy = init_action(ELV, NULL, 300);
	cpy->finish.tv_sec = act->finish.tv_sec;
	cpy->finish.tv_usec = act->finish.tv_usec;
	if (pl->a_first == NULL)
	{
		pl->a_first = cpy;
		pl->a_last = cpy;
	}
	else
	{
		cpy->next = pl->a_first;
		pl->a_first->prev = cpy;
		pl->a_first = cpy;
	}
}

int		check_lvl_elev(t_caps *bwscps, int lvl, int nb)
{
	int			count;

	count = 0;
	while (bwscps)
	{
		if (bwscps->player && bwscps->player->lvl == lvl)
			count++;
		bwscps = bwscps->next;
	}
	if (count < nb)
		return (-1);
	return (0);
}

int		check_lvl7(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 6))
		return (-1);
	if (spot->linemate < 2 || spot->deraumere < 2 || spot->sibur < 2
		|| spot->mendiane < 2 || spot->phiras < 1 || spot->thystame < 1)
		return (-1);
	return (0);
}

int		check_lvl6(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 6))
		return (-1);
	if (spot->linemate < 1 || spot->deraumere < 2
		|| spot->sibur < 3 || spot->phiras < 1)
		return (-1);
	return (0);
}

int		check_lvl5(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 4))
		return (-1);
	if (spot->linemate < 1 || spot->deraumere < 2
		|| spot->sibur < 1 || spot->mendiane < 3)
		return (-1);
	return (0);
}

int		check_lvl4(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 4))
		return (-1);
	if (spot->linemate < 1 || spot->deraumere < 1
		|| spot->sibur < 2 || spot->phiras < 1)
		return (-1);
	return (0);
}

int		check_lvl3(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 2))
		return (-1);
	if (spot->linemate < 2 || spot->sibur < 1 || spot->phiras < 2)
		return (-1);
	return (0);
}

int		check_lvl2(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;
	t_caps		*bwscps;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	bwscps = zp->map[pl->pos_y][pl->pos_x].list;
	if (check_lvl_elev(bwscps, pl->lvl, 2))
		return (-1);
	if (spot->linemate < 1 || spot->deraumere < 1 || spot->sibur < 1)
		return (-1);
	return (0);
}

int		check_lvl1(t_player *pl, t_zaap *zp)
{
	t_stock		*spot;

	spot = zp->map[pl->pos_y][pl->pos_x].ressources;
	if (spot->linemate < 1)
		return (-1);
	return (0);
}

int		check_elev(t_player *pl, t_zaap *zaap)
{
	int		ret;

	ret = -1;
	if (pl->lvl == 1)
		ret = check_lvl1(pl, zaap);
	else if (pl->lvl == 2)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 3)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 4)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 5)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 6)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 7)
		ret = check_lvl2(pl, zaap);
	else if (pl->lvl == 8)
		ret = -1;
	return (ret);
}

void	send_start_elv_gfx(t_player *pl, t_zaap *zaap)
{
	char		tmp[BUFF + 1];
	char		*tmp2;
	char		*tmp3;
	char		*tmp4;
	t_caps		*bwscps;

	bwscps = zaap->map[pl->pos_y][pl->pos_x].list;
	sprintf(tmp, "pic %d %d %d #%d ", pl->pos_x, pl->pos_y, pl->lvl, pl->sock);
	tmp2 = ft_strnew(0);
	while (bwscps)
	{
		if (bwscps->player && bwscps->player->lvl == pl->lvl
			&& bwscps->player != pl)
		{
			tmp3 = ft_itoa(bwscps->player->sock);
			tmp4 = ft_strjoin("#", tmp3);
			ft_addnstr(&tmp2, 1, 1, tmp4);
			ft_free_all_four(tmp3, tmp4, NULL, NULL);
		}
		bwscps = bwscps->next;
	}
	tmp3 = ft_strjoin(tmp, tmp2);
	add_to_gfx_buf(zaap->gfx, tmp3);
	ft_free_all_four(tmp3, tmp2, NULL, NULL);
}

void	send_failed_elv_gfx(t_player *pl, t_gfx *gfx)
{
	char	tmp[BUFF + 1];

	sprintf(tmp, "pie %d %d 0\n", pl->pos_x, pl->pos_y);
	add_to_gfx_buf(gfx, tmp);
}

void	start_elev(t_action *act, t_player *pl, t_zaap *zaap)
{
	t_caps		*bwscps;

	if (zaap->gfx)
		send_start_elv_gfx(pl, zaap);
	if (check_elev(pl, zaap))
	{
		add_player_buff(pl, "ko\n");
		prep_next_act(act, pl, zaap);
		if (zaap->gfx)
			send_failed_elv_gfx(pl, zaap->gfx);
	}
	else
	{
		bwscps = zaap->map[pl->pos_y][pl->pos_x].list;
		while (bwscps)
		{
			if (bwscps->player && (bwscps->player->lvl == pl->lvl))
			{
				add_player_buff(bwscps->player, "elevation en cours\n");
				if (bwscps->player != pl)
					add_action_front(act, bwscps->player);
			}
			bwscps = bwscps->next;
		}
	}
}

void	prep_next_act(t_action *act, t_player *pl, t_zaap *zaap)
{
	if (act->next == NULL)
	{
		pl->a_first = NULL;
		pl->a_last = NULL;
	}
	else if (act->next)
	{
		pl->a_first = act->next;
		pl->a_first->prev = NULL;
		action_time(&(pl->a_first->finish), zaap->time, pl->a_first->lenght);
		if (pl->a_first->type == FRK && zaap->gfx)
			send_hatching_gfx(pl->sock, zaap->gfx);
		else if (pl->a_first->type == ELV)
			start_elev(pl->a_first, pl, zaap);
	}
	free(act);
}

void	make_action(t_action *act, t_player *pl, t_zaap *zaap)
{
	int		i;
	t_pac	*parse;

	i = 0;
	parse = get_parse_make();
	while (i < 12)
	{
		if (parse[i].type == act->type)
			parse[i].fn(act, pl, zaap);
		i++;
	}
	prep_next_act(act, pl, zaap);
}

void	player_game(t_player *pl, t_zaap *zaap)
{
	if (check_food(pl, zaap))
		return ;
	if (pl->a_first)
	{
		if (is_time_yet(pl->a_first->finish))
		{
			make_action(pl->a_first, pl, zaap);
			if (pl->nba)
				pl->nba--;
		}
	}
}

void	rotten_egg(t_egg *egg, t_team *team, t_zaap *zaap)
{
	char	ret[BUFF + 1];

	if (zaap->gfx)
	{
		sprintf(ret, "edi #%d\n", egg->nb);
		add_to_gfx_buf(zaap->gfx, ret);
	}
	remove_egg_map(egg, zaap);
	remove_egg_team(egg, team);
	if (team->places)
		(team->places)--;
}

void	hatching_egg(t_egg *egg, t_team *team, t_zaap *zaap)
{
	char	ret[BUFF  +1];

	egg->ok = 1;
	team->places++;
	action_time(&(egg->hatch), zaap->time, 1260);
	if (zaap->gfx)
	{
		sprintf(ret, "eht #%d\n", egg->nb);
		add_to_gfx_buf(zaap->gfx, ret);
	}
}

void	check_eggs(t_team *team, t_zaap *zaap)
{
	t_egg	*bwseg;
	t_egg	*keep;

	if (team->eggs == NULL)
		return ;
	bwseg = team->eggs;
	while (bwseg)
	{
		keep = bwseg->next;
		if (bwseg->ok && is_time_yet(bwseg->hatch))
			rotten_egg(bwseg, team, zaap);
		else if (!bwseg->ok && is_time_yet(bwseg->hatch))
			hatching_egg(bwseg, team, zaap);
		bwseg = keep;
	}
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
