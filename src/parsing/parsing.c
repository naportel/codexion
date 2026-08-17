/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:36:56 by naportel          #+#    #+#             */
/*   Updated: 2026/08/17 11:37:24 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long	ft_latoi(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return (result);
}

static int	ft_is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_schedule(char *schedule)
{
	if (strcmp(schedule, "fifo") == 0)
		return (0);
	else if (strcmp(schedule, "edf") == 0)
		return (1);
	else
		return (2);
}

int	parse_args(int ac, char **av, t_table *table)
{
	int		i;
	int		scheduler;
	long	temp;

	i = 1;
	if (ac != 9)
		return (error("The program expects 8 arguments."));
	while (i < 8)
	{
		if (!ft_is_valid_number(av[i++]))
			return (error("Arguments 1-7 must contain only positive digits!"));
		temp = ft_latoi(av[i - 1]);
		if (temp == -1)
			return (error("Arguments must be valid digits within INT_MAX!"));
	}
	if (ft_latoi(av[1]) < 1)
		return (error("There must be at least 1 coder!"));
	else if (ft_latoi(av[6]) < 1)
		return (0);
	scheduler = parse_schedule(av[8]);
	if (scheduler == 2)
		return (error("Scheduler must be exactly either \"fifo\" or \"edf\"!"));
	*table = define_table(av, scheduler);
	return (1);
}

t_table	define_table(char **av, int scheduler)
{
	t_table	table;

	table.coder_qnt = ft_latoi(av[1]);
	table.burnout = ft_latoi(av[2]);
	table.comp_time = ft_latoi(av[3]);
	table.debug_time = ft_latoi(av[4]);
	table.refactor_time = ft_latoi(av[5]);
	table.comps_need = ft_latoi(av[6]);
	table.dongle_cooldown = ft_latoi(av[7]);
	table.scheduler = scheduler;
	table.simulation_run = 1;
	return (table);
}
