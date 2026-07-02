/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:01:42 by naportel          #+#    #+#             */
/*   Updated: 2026/06/22 14:03:28 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_table(t_table *table)
{
	int	i;

	i = 0;
	table->dongles = malloc(sizeof(t_dongle) * table->coder_qnt);
	table->coders = malloc(sizeof(t_coder) * table->coder_qnt);
	if (!table->dongles || !table->coders)
		return (error("Malloc Failed!"));
	pthread_mutex_init(&table->log_mutex, NULL);
	while (i < table->coder_qnt)
	{
		table->coders[i].id = i + 1;
		i++;
	}
	i = 0;
	while (i < table->coder_qnt)
	{
		pthread_mutex_init(&table->dongles[i].mutex, NULL);
		pthread_cond_init(&table->dongles[i].cond, NULL);
		if (!init_heap(&table->dongles[i].heap, table->coder_qnt))
			return (error("Malloc Faield!"));
		i++;
	}
	return (1);
}

int	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->coder_qnt)
	{
		if (pthread_create(&table->coders[i].thread, NULL,
				coder_routine, &table->coders[i]) != 0)
		{
			error("Thread Creation Failed!");
			return (0);
		}
		i++;
	}
	pthread_create(&table->monitor, NULL, monitor_routine, table);
	return (1);
}

void	cleanup_table(t_table *table)
{
	int	i;

	i = 0;
	if (table->dongles)
	{
		while (i < table->coder_qnt)
		{
			pthread_mutex_destroy(&table->dongles[i].mutex);
			pthread_cond_destroy(&table->dongles[i].cond);
			i++;
		}
		free(table->dongles);
	}
	if (table->coders)
		free(table->coders);
	pthread_mutex_destroy(&table->log_mutex);
}
