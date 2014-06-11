/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:28 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/11 21:49:45 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "zaap.h"
#include "libft.h"

void	init_players_fd(t_player *bwspl, t_zaap *zaap)
{
	while (bwspl)
	{
		if (ft_strlen(bwspl->buff_wr) > 0)
			FD_SET(bwspl->sock, &zaap->fd_wr);
		else
			FD_SET(bwspl->sock, &zaap->fd_rd);
		zaap->max = ft_isgreater(zaap->max, bwspl->sock);
		bwspl = bwspl->next;
	}
}

void	init_gfx_fd(t_zaap *zaap)
{
	if (zaap->gfx)
	{
		if (zaap->gfx->to_send > 0)
			FD_SET(zaap->gfx->sock, &zaap->fd_wr);
		else
			FD_SET(zaap->gfx->sock, &zaap->fd_rd);
		zaap->max = ft_isgreater(zaap->max, zaap->gfx->sock);
	}
}

void	init_fd(t_zaap *zaap)
{
	t_team		*bwst;
	t_temp		*bwstmp;

	zaap->max = zaap->sock;
	FD_ZERO(&zaap->fd_rd);
	FD_ZERO(&zaap->fd_wr);
	FD_SET(zaap->sock, &zaap->fd_rd);
	bwstmp = zaap->wait;
	bwst = zaap->teams;
	init_gfx_fd(zaap);
	while (bwstmp)
	{
		if (ft_strlen(bwstmp->buff_wr) > 0)
			FD_SET(bwstmp->sock, &zaap->fd_wr);
		else
			FD_SET(bwstmp->sock, &zaap->fd_rd);
		zaap->max = ft_isgreater(zaap->max, bwstmp->sock);
		bwstmp = bwstmp->next;
	}
	while (bwst)
	{
		if (bwst->first)
			init_players_fd(bwst->first, zaap);
		bwst = bwst->next;
	}
}

t_temp		*init_tmp(int sock)
{
	t_temp		*new;

	if ((new = (t_temp *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->sock = sock;
	new->buff_rd[0] = '\0';
	new->buff_wr[0] = '\0';
	ft_strcat(new->buff_wr, "BIENVENUE\n");
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_tmp(t_temp *tmp, t_zaap *zaap)
{
	t_temp		*bwstmp;

	if (zaap->wait == NULL)
		zaap->wait = tmp;
	else
	{
		bwstmp = zaap->wait;
		while (bwstmp->next)
			bwstmp = bwstmp->next;
		bwstmp->next = tmp;
		tmp->prev = bwstmp;
	}
}

void	accept_client(t_zaap *zaap)
{
	int						cs;
	int						port;
	struct sockaddr_in		csin;
	socklen_t				csin_len;
	t_temp					*tmp;

	csin_len = sizeof(csin);
	if ((cs = accept(zaap->sock, (struct sockaddr*)&csin, &csin_len)) == -1)
		return ;
	port = ntohs(csin.sin_port);
	printf("New client #%d from %s:%d\n", cs, inet_ntoa(csin.sin_addr), port);
	tmp = init_tmp(cs);
	add_tmp(tmp, zaap);
}

void	write_tmp(t_temp *tmp)
{
	send(tmp->sock, tmp->buff_wr, ft_strlen(tmp->buff_wr), 0);
	ft_strclr(tmp->buff_wr);
}

int		find_read(char *str)
{
	int		ret;

	ret = 0;
	while (*str)
	{
		if (*str == '\n')
			break ;
		str++;
		ret++;
	}
	if (*str == '\0')
		return (-1);
	return (ret);
}

//attention au remove dans le read, mettre un flag

void	remove_tmp(t_temp *tmp, t_zaap *zaap)
{
//	close(tmp->sock);
	if (tmp->prev == NULL && tmp->next == NULL)
		zaap->wait = NULL;
	else if (tmp->prev && tmp->next == NULL)
		tmp->prev->next = NULL;
	else if (tmp->prev == NULL && tmp->next)
	{
		zaap->wait = tmp->next;
		tmp->next->prev = NULL;
	}
	else if (tmp->prev && tmp->next)
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
	}
	free(tmp);
}

t_gfx		*init_gfx(int sock)
{
	t_gfx	*new;

	if ((new = (t_gfx *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->sock = sock;
	new->to_send = 0;
	new->list = NULL;
	return (new);
}

t_team		*check_teams(char *str, t_team *bwst)
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

t_player	*init_player(int sock)
{
	t_player	*new;

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

t_caps	*init_caps(t_player *player, t_egg *egg)
{
	t_caps	*new;

	if ((new = (t_caps *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->player = NULL;
	new->egg = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (player)
		new->player = player;
	else if (egg)
		new->egg = egg;
	return (new);
}

void	add_player_to_map(t_player *player, t_zaap *zaap)
{
	t_caps		*bwscps;
	t_caps		*new_pos;

	new_pos = init_caps(player, NULL);
	bwscps = zaap->map[player->pos_y][player->pos_x].list;
	if (bwscps == NULL)
		zaap->map[player->pos_y][player->pos_x].list = new_pos;
	else
	{
		while (bwscps->next)
			bwscps = bwscps->next;
		bwscps->next = new_pos;
		new_pos->prev = bwscps;
	}
}

void	remove_egg_map(t_egg *egg, t_zaap *zaap)
{
//	t_map	spot;
	t_caps	*bwscps;

	bwscps = zaap->map[egg->y][egg->x].list;
	while (bwscps)
	{
		if (bwscps->egg == egg)
		{
			if (bwscps->prev == NULL && bwscps->next == NULL)
				zaap->map[egg->y][egg->x].list = NULL;
			else if (bwscps->prev == NULL && bwscps->next)
			{
				zaap->map[egg->y][egg->x].list = bwscps->next;
				bwscps->prev = NULL;
			}
			else if (bwscps->prev && bwscps->next)
			{
				bwscps->next->prev = bwscps->prev;
				bwscps->prev->next = bwscps->next;
			}
			else if (bwscps->prev && bwscps->next == NULL)
				bwscps->prev->next = NULL;
			free(bwscps);
			return ;
		}
		bwscps = bwscps->next;
	}
}

void	place_player_rand(t_player *new, t_zaap *zaap)
{
	new->pos_x = rand_a_b(0, zaap->x);
	new->pos_y = rand_a_b(0, zaap->y);
	add_player_to_map(new, zaap);
}

t_egg	*egg_rdy(t_egg *bwsegg)
{
	while (bwsegg)
	{
		if (bwsegg->hatch <= time(NULL)) //A REFAIRE
			return (bwsegg);
		bwsegg = bwsegg->next;
	}
	return (NULL);
}

void	remove_egg_team(t_egg *egg, t_team *team)
{
	if (egg->prev == NULL && egg->next == NULL)
		team->eggs = NULL;
	else if (egg->prev == NULL && egg->next)
	{
		team->eggs = egg->next;
		egg->next->prev = NULL;
	}
	else if (egg->prev && egg->next)
	{
		egg->prev->next = egg->next;
		egg->next->prev = egg->prev;
	}
	else if (egg->prev && egg->next == NULL)
		egg->prev->next = NULL;
	free(egg);
}

void	place_player_in_egg(t_team *tm, t_player *new, t_egg *egg, t_zaap *zaap)
{
	new->pos_x = egg->x;
	new->pos_y = egg->y;
	add_player_to_map(new, zaap);
	remove_egg_map(egg, zaap);
	remove_egg_team(egg, tm);
}

void	add_new_client(t_team *team, int sock, t_zaap *zaap)
{
	t_player	*bwspl;
	t_player	*new;
	t_egg		*egg;

	new = init_player(sock);
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

void	treat_tmp(t_temp *tmp, t_zaap *zaap)
{
	t_team		*team;

	if (!ft_strcmp(tmp->buff_rd, "GRAPHIC\n"))
	{
		if (zaap->gfx)
			ft_strcat(tmp->buff_wr, "There is already a gfx client\n");
		else
		{
			zaap->gfx = init_gfx(tmp->sock);
			remove_tmp(tmp, zaap);
		}
	}
	else if ((team = check_teams(tmp->buff_rd, zaap->teams)) != NULL)
	{
		add_new_client(team, tmp->sock, zaap);
		remove_tmp(tmp, zaap);
	}
	else
		ft_strcat(tmp->buff_wr, "I don't understand you...\n");
}

void	read_tmp(t_temp *tmp, t_zaap *zaap)
{
	int		ret;
	int		read;

	read = -1;
	if ((ret = recv(tmp->sock, tmp->buff_rd, BUFF, MSG_PEEK)) > 0)
	{
		tmp->buff_rd[ret] = '\0';
		read = find_read(tmp->buff_rd);
		if (read > -1)
		{
			ret = recv(tmp->sock, tmp->buff_rd, read + 1, 0);
			if (ret <= 0)
			{
				remove_tmp(tmp, zaap);
				return ;
			}
			tmp->buff_rd[ret] = '\0';
			printf("Receive from %d: %s", tmp->sock, tmp->buff_rd);
			treat_tmp(tmp, zaap);
		}
	}
	else if (ret <= 0)
		remove_tmp(tmp, zaap);
}

void	check_tmp_fd(t_temp *bwstmp, t_zaap *zaap)
{
	while (bwstmp)
	{
		if (FD_ISSET(bwstmp->sock, &zaap->fd_wr))
			write_tmp(bwstmp);
		else if (FD_ISSET(bwstmp->sock, &zaap->fd_rd))
			read_tmp(bwstmp, zaap);
		bwstmp = bwstmp->next;
	}
}

void	write_player(t_player *player)
{
	send(player->sock, player->buff_wr, ft_strlen(player->buff_wr), 0);
	ft_strclr(player->buff_wr);
}

void	free_actions(t_action *list)
{
	t_action	*keep;

	while (list)
	{
		keep = list->next;
		free(list);
		list = keep;
	}
}

void	remove_pl(t_player *pl, t_team *team)
{
	close(pl->sock);
	if (pl->prev == NULL && pl->next == NULL)
		team->first = NULL;
	else if (pl->prev && pl->next == NULL)
		pl->prev->next = NULL;
	else if (pl->prev == NULL && pl->next)
	{
		team->first = pl->next;
		pl->next->prev = NULL;
	}
	else if (pl->prev && pl->next)
	{
		pl->prev->next = pl->next;
		pl->next->prev = pl->prev;
	}
	if (pl->inventory)
		free(pl->inventory);
	if (pl->a_first)
		free_actions(pl->a_first);
	free(pl);
}

void	treat_player(t_player *player, t_zaap *zaap)
{
	(void)zaap;
	ft_strclr(player->buff_rd);//FAKE
	ft_strcat(player->buff_wr, "CMD OK\n"); //FAKE
}

void	read_player(t_player *pl, t_zaap *zaap, t_team *team)
{
	int		ret;
	int		read;

	read = -1;
	if ((ret = recv(pl->sock, pl->buff_rd, BUFF, MSG_PEEK)) > 0)
	{
		pl->buff_rd[ret] = '\0';
		read = find_read(pl->buff_rd);
		if (read > -1)
		{
			ret = recv(pl->sock, pl->buff_rd, read + 1, 0);
			if (ret <= 0)
			{
				remove_pl(pl, team);
				return ;
			}
			pl->buff_rd[ret] = '\0';
			printf("Player %d in team %s: %s", pl->sock, team->name, pl->buff_rd);
			treat_player(pl, zaap);
		}
	}
	else if (ret <= 0)
		remove_pl(pl, team);
}

void	check_players_fd(t_player *bwspl, t_zaap *zaap, t_team *team)
{
	while (bwspl)
	{
		if (FD_ISSET(bwspl->sock, &zaap->fd_wr))
			write_player(bwspl);
		else if (FD_ISSET(bwspl->sock, &zaap->fd_rd))
			read_player(bwspl, zaap, team);
		bwspl = bwspl->next;
	}
}

void	write_to_gfx(t_gfx *gfx)
{
	char	*to_send;
	t_buff	*bwsbuf;
	t_buff	*keep;

	bwsbuf = gfx->list;
	to_send = ft_strnew(gfx->to_send);
	while (bwsbuf)
	{
		ft_strcat(to_send, bwsbuf->buff_wr);
		bwsbuf = bwsbuf->next;
	}
	send(gfx->sock, to_send, gfx->to_send, 0);
	gfx->to_send = 0;
	bwsbuf = gfx->list;
	while (bwsbuf)
	{
		keep = bwsbuf->next;
		free(bwsbuf);
		bwsbuf = keep;
	}
	gfx->list = NULL;
}

void	add_to_gfx_buf(t_gfx *gfx, char *str)
{
	t_buff		*new;
	t_buff		*bws;

//	printf("ADD GFX BUFF IN\n");
	if ((new = (t_buff *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->buff_wr[0] = '\0';
	ft_strcat(new->buff_wr, str);
	new->next = NULL;
	if (gfx->list == NULL)
		gfx->list = new;
	else
	{
		bws = gfx->list;
		while (bws->next)
			bws = bws->next;
		bws->next = new;
	}
	gfx->to_send += ft_strlen(str);
//	printf("ADD GFX BUFF OUT\n");
}

void	treat_gfx(t_gfx *gfx, t_zaap *zaap)
{
	(void)zaap;
	add_to_gfx_buf(gfx, "AHMED BOUFFON\n");
	add_to_gfx_buf(gfx, "msz 20 20\n");
	ft_strclr(gfx->buff_rd);
}

void	read_gfx(t_gfx *gfx, t_zaap *zaap)
{
	int		ret;
	int		read;

	read = -1;
	if ((ret = recv(gfx->sock, gfx->buff_rd, BUFF, MSG_PEEK)) > 0)
	{
		gfx->buff_rd[ret] = '\0';
		read = find_read(gfx->buff_rd);
		if (read > -1)
		{
			ret = recv(gfx->sock, gfx->buff_rd, read + 1, 0);
			if (ret <= 0)
			{
//				remove_pl(pl, team);
				return ;
			}
			gfx->buff_rd[ret] = '\0';
			printf("GFX said: %s", gfx->buff_rd);
			treat_gfx(gfx, zaap);
		}
	}
//	else if (ret <= 0)
//		remove_pl(pl, zaap);
}

void	check_gfx(t_zaap *zaap, t_gfx *gfx)
{
	if (zaap->gfx)
	{
		if (FD_ISSET(gfx->sock, &zaap->fd_wr))
			write_to_gfx(gfx);
		else if (FD_ISSET(gfx->sock, &zaap->fd_rd))
			read_gfx(gfx, zaap);
	}
}

void	check_fd(int ret, t_zaap *zaap)
{
	t_team		*bwst;

	if (ret <= 0)
		return ;
	bwst = zaap->teams;
	if (FD_ISSET(zaap->sock, &zaap->fd_rd))
		accept_client(zaap);
//	printf("accept IN\n");
	check_gfx(zaap, zaap->gfx);
//	printf("accept OUT\n");
	check_tmp_fd(zaap->wait, zaap);
	while (bwst)
	{
		check_players_fd(bwst->first, zaap, bwst);
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
//		check_actions(zaap); //a faire
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
