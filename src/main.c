/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:03:57 by naportel          #+#    #+#             */
/*   Updated: 2026/06/22 14:02:33 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!parse_args(ac, av, &table))
		return (0);
	codexion(&table);
	return (0);
}

void	codexion(t_table *table)
{
	if (!init_table(&table) || !init_threads(&table))
	{
		cleanup_table(&table);
		return ;
	}
	while (check_simulation(table))
	{
		if (table->scheduler == fifo)
			fifo_scheduler(&table);
		else if (table->scheduler == edf)
			edf_scheduler(&table);
		table->comps_done++;
	}
}
