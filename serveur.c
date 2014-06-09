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

#include "zaap.h"
#include "libft.h"

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
	exit(code);
}

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

void		get_arg(t_zaap *zaap, char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "-x") && arg[i + 1])
			zaap->x = ft_atoi(arg[i + 1]);
		else if (!ft_strcmp(arg[i], "-p") && arg[i + 1])
			zaap->port = ft_atoi(arg[i + 1]);
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
}

void		init_zaap(t_zaap *zaap)
{
	zaap->sock = -1;
	zaap->port = -1;
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

t_stock		*gen_ressources(void)
{
	t_stock		*inv;

	inv = get_inv();
}

void		init_case(t_map spot)
{
	spot->ressources = gen_ressources();
	spot->list = NULL;
}

t_map		*init_map(t_map **map, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			init_case(map[i][j]);
			j++;
		}
		i++;
	}
	return (map);
}

void		get_map(t_zaap *zaap)
{
	t_map	**map;
	int		y;

	y = 0;
	if (zaap->x < 20 || zaap->y < 20)
		zaap_error(-4);
	if ((map = (map**)malloc(sizeof(map) * (zaap->y + 1))) == NULL)
		zaap_error(-2);
	map[zaap->y] = NULL;
	while (map[y])
	{
		map[y] = (map*)malloc(sizeof(map) * (zaap->x + 1));
		map[y][zaap->x] = NULL;
		y++;
	}
	map = init_map(map);
	zaap->map = &map;
}

t_zaap		*get_zaap(char **arg)
{
	t_zaap	*new;

	if ((new = (t_zaap *)malloc(sizeof(*new))) == NULL)
		zaap_error(-2);
	init_zaap(new);
	get_arg(new, arg);
	get_map(new);
//	get_sock(zaap);
	return (new);
}

int		main(int argc, char **argv)
{
	t_zaap		*zaap;

	if (argc < 12)
		zaap_error(-1);
	zaap = get_zaap(argv);
//	loop_map(zaap);
//	exit_zaapy(zaap);
}
