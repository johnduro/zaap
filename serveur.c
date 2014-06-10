/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/09 17:36:28 by mle-roy           #+#    #+#             */
/*   Updated: 2014/06/09 22:28:22 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include "zaap.h"
#include "libft.h"

/*
int		zaap_error(int code)
{
	if (code == -1)
	{
		ft_putstr_fd(USAGE1, 2);
		ft_putstr_fd(USAGE2, 2);
	}
	else if (code == -2)
		ft_putstr_fd("Malloc error\n", 2);
	else if (code == -3)
		ft_putstr_fd("Team name too long\n", 2);
	else if (code == -4)
		ft_putstr_fd("Minimum size for x or y is 20\n", 2);
	else if (code == -5)
		ft_putstr_fd("Wrong port number\n", 2);
	else if (code == -6)
		ft_putstr_fd("Sock error\n", 2);
	else if (code == -7)
		ft_putstr_fd("Bind error\n", 2);
	exit(code);
}
*/

void		add_team(t_zaap *zaap, char *name)
{
	t_team	*new;
	t_team	*bwst;

	if ((new = (t_team *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	ft_strcpy(new->name, name);
	new->player_nb = 0;
	new->first = NULL;
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

void		get_teams(t_zaap *zaap, char **arg, int i)
{
	while (arg[i] && arg[i][0] != '-')
	{
		if (ft_strlen(arg[i]) > BUFF_NAME)
			zaap_error(-3);
		else
			add_team(zaap, arg[i]);
		i++;
	}
}

int			get_arg(t_zaap *zaap, char **arg)
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
	return (port);
}

void		init_zaap(t_zaap *zaap)
{
	zaap->sock = -1;
//	zaap->port = -1;
	zaap->x = -1;
	zaap->y = -1;
	zaap->nb_start = -1;
	zaap->time = -1;
	zaap->map = NULL;
	zaap->wait = NULL;
	zaap->teams = NULL;
	zaap->eggs = NULL;
}

t_stock		*get_inv(void)
{
	t_stock		*new;

	if ((new = (t_stock *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	new->food = 0;
	new->linemate = 0;
	new->deraumere = 0;
	new->sibur = 0;
	new->mendiane = 0;
	new->phiras = 0;
	new->thystame = 0;
	return (new);
}

int			rand_a_b(int a, int b)
{
	return (rand() % ((b - a) + a));
}

t_stock		*gen_ressources(void)
{
	t_stock		*inv;

	inv = get_inv();
	inv->food = rand_a_b(1, 11);
	inv->linemate = rand_a_b(0, 11);
	inv->deraumere = rand_a_b(0, 10);
	inv->sibur = rand_a_b(0, 9);
	inv->mendiane = rand_a_b(0, 5);
	inv->phiras = rand_a_b(0, 4);
	inv->thystame = rand_a_b(0, 3);
	return (inv);
}

void		init_case(t_map spot)
{
	(void)spot;
	spot.ressources = gen_ressources();
	spot.list = NULL;
}

void		init_map(t_zaap *zaap)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	srand(time(NULL));
//	while (map[i])
	while (i < zaap->y)
	{
		j = 0;
//		while (map[i][j])
		while (j < zaap->x)
		{
//			init_case(map[i][j]);
//			init_case(zaap->map[i][j]);
			zaap->map[i][j].ressources = gen_ressources();
			zaap->map[i][j].list = NULL;
			j++;
		}
		i++;
	}
//	return (map);
}

void		get_map(t_zaap *zaap)
{
	t_map	**map;
	int		y;

	y = 0;
	if (zaap->x < 20 || zaap->y < 20)
		zaap_error(-4);
	(void)map;
//	if ((map = (t_map**)malloc(sizeof(map) * (zaap->y + 1))) == NULL)
//		zaap_error(-2);
	if ((zaap->map = (t_map**)malloc(sizeof(map) * (zaap->y + 1))) == NULL)
		zaap_error(-2);
//	map[zaap->y] = NULL;
//	while (map[y])
	while (y < zaap->y)
	{
		zaap->map[y] = (t_map*)malloc(sizeof(map) * (zaap->x + 1));
//		map[y] = (t_map*)malloc(sizeof(map) * (zaap->x + 1));
//		map[y][zaap->x] = NULL;
		y++;
	}
//	zaap->map = init_map(map, zaap);
	init_map(zaap);
//	map = init_map(map, zaap);
//	zaap->map = &map;
}

void		get_sock(t_zaap *zaap, int port)
{
	struct sockaddr_in		sin;
	struct protoent			*pe;

	if (port < 1024)
		zaap_error(-5);
	pe = getprotobyname("tcp");
	zaap->sock = socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (zaap->sock == -1)
		zaap_error(-6);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	if ((bind(zaap->sock, (struct sockaddr*)&sin, sizeof(sin))) == -1)
		zaap_error(-7);
	listen(zaap->sock, 42);
}

t_zaap		*get_zaap(char **arg)
{
	t_zaap	*new;
	int		port;

	port = -1;
	if ((new = (t_zaap *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	init_zaap(new);
	port = get_arg(new, arg);
	get_map(new);
	get_sock(new, port);
	return (new);
}
/*
void	print_case(t_map yolo, int nb, int x, int y)
{
//	t_stock		*tmp;
//	write(1, "lalala\n", 7);
//	(void)yolo;
//	(void)nb;
//	(void)x;
//	(void)y;

	printf("Case n*%d pos[%d][%d]\n", nb, x, y);
//	tmp = yolo.ressources;
//	printf("TEST %d TEST\n", tmp->linemate);
	printf("Linemate %d, ", yolo.ressources->linemate);
	printf("deraumere %d, ", yolo.ressources->deraumere);
	printf("sibur %d, ", yolo.ressources->sibur);
	printf("mendiane %d, ", yolo.ressources->mendiane);
	printf("phiras %d, ", yolo.ressources->phiras);
	printf("thystame %d\n", yolo.ressources->thystame);
}

void	debug_map(t_map **map, t_zaap *zaap)
{
	int		i;
	int		j;
	int		all;

	i = 0;
	j = 0;
	all = 1;
//	while (map[i])
	while (i < zaap->y)
	{
		j = 0;
//		while (map[i][j])
		while (j < zaap->x)
		{
			printf("i=%d, j=%d\n", i, j);
			print_case(map[i][j], all, i, j);
			all++;
			j++;
		}
		i++;
	}
}

void	print_teams(t_team *team)
{
	int		nb;

	nb = 1;
	while (team)
	{
		printf("team n*%d: %s\n", nb, team->name);
		team = team->next;
	}
}

void	debug_1(t_zaap *zaap)
{
	printf("Sock = %d\n", zaap->sock);
	printf("x = %d || y = %d\n", zaap->x, zaap->y);
	printf("nb_start = %d\n", zaap->nb_start);
	printf("time = %d\n", zaap->time);
	debug_map(zaap->map, zaap);
	if (zaap->teams)
		print_teams(zaap->teams);
}
*/

int		main(int argc, char **argv)
{
	t_zaap		*zaap;

	if (argc < 12)
		zaap_error(-1);
	zaap = get_zaap(argv);
	debug_1(zaap);
//	loop_map(zaap);
//	exit_zaapy(zaap);
	return (0);
}
