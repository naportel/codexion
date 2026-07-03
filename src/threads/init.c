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
		init_coder(table, &table->coders[i], i);
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

void	init_coder(t_table *table, t_coder *coder, int id)
{
	coder->id = id;
	coder->comps_done = 0;
	coder->last_comp = get_current_time();
	pthread_mutex_init(coder->coder_mutex);
	coder->table = table;
	coder->left_dongle = table->dongles[2 * id + 1];
	coder->right_dongle = table->dongles[2 * id + 2];
	return ;
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
			return error("Thread Creation Failed!");
		}
		i++;
	}
	pthread_create(&table->monitor, NULL, monitor_routine, table);
	return (1);
}

void	free_table(t_table *table)
{
	int	i;

	i = 0;
	if (table->dongles)
	{
		while (i < table->coder_qnt)
		{
			free(table->dongles[i].heap.data)
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
