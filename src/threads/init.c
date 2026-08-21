/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 19:36:00 by naportel          #+#    #+#             */
/*   Updated: 2026/08/14 19:45:11 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_table(t_table *table)
{
	int	i;

	i = 0;
	table->dongles = malloc(sizeof(t_dongle) * table->coder_qnt);
	table->coders = malloc(sizeof(t_coder) * table->coder_qnt);
	table->start_time = get_time();
	if (!table->dongles || !table->coders)
		return (error("Malloc Failed!"));
	pthread_mutex_init(&table->state_mutex, NULL);
	pthread_mutex_init(&table->log_mutex, NULL);
	while (i < table->coder_qnt)
	{
		init_coder(table, &table->coders[i], i);
		i++;
	}
	i = 0;
	while (i < table->coder_qnt)
	{
		if (!init_dongle(&table->dongles[i], table->coder_qnt))
			return (0);
		i++;
	}
	return (1);
}

int	init_dongle(t_dongle *dongle, int capacity)
{
	pthread_mutex_init(&dongle->mutex, NULL);
	pthread_cond_init(&dongle->cond, NULL);
	if (!init_heap(&dongle->heap, capacity))
		return (error("Malloc Failed!"));
	dongle->holder = NULL;
	dongle->available_at = get_time();
	return (1);
}

void	init_coder(t_table *table, t_coder *coder, int id)
{
	coder->id = id;
	coder->comps_done = 0;
	coder->last_comp = get_time();
	pthread_mutex_init(&coder->coder_mutex, NULL);
	coder->table = table;
	coder->left_dongle = &table->dongles[id];
	coder->right_dongle = &table->dongles[(id + 1) % table->coder_qnt];
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
			return (error("Thread Creation Failed!"));
		}
		i++;
	}
	pthread_create(&table->monitor, NULL, monitor_routine, table);
	return (1);
}
