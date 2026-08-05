/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:36:56 by naportel          #+#    #+#             */
/*   Updated: 2026/08/05 16:11:26 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
	int	i;
	int mune;

	i = 1;
	if (ac != 9)
		return (error("Thr program expects 8 arguments."));
	while (i < 8)
		if (!ft_isnumber(av[i++]))
			return (error("The 1-7th arguments must be Positive Integers!"));
	mune = parse_schedule(av[8])
	if (mune >= 2)
		return error("Scheduler must be exactly either \"fifo\" or \"edf\"!");
	*table = (t_table){
		.coder_qnt = atoi(av[1]),
		.burnout = atoi(av[2]),
		.comp_time = atoi(av[3]),
		.debug_time = atoi(av[4]),
		.refactor_time = atoi(av[5]),
		.comps_need = atoi(av[6]),
		.dongle_cooldown = atoi(av[7]),
		.scheduler = mune
    }
	return (1);
}

int	ft_isnumber(char *str)
{
	int	result;

	result = atoi(str);
	if (result == 0)
		return (0);
}
