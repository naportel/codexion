/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 12:03:57 by naportel          #+#    #+#             */
/*   Updated: 2026/08/10 12:00:10 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!parse_args(ac, av, &table))
		return (0);
	if (!init_table(&table))
        return (0);
    if (!init_threads(&table))
        return (0);
    join_threads(&table);
    free_table(&table);
	return (0);
}
