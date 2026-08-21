/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:01:42 by naportel          #+#    #+#             */
/*   Updated: 2026/08/21 13:57:41 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	free_dongles(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->coder_qnt)
	{
		free(table->dongles[i].heap.data);
		pthread_mutex_destroy(&table->dongles[i].mutex);
		pthread_cond_destroy(&table->dongles[i].cond);
		i++;
	}
	free(table->dongles);
}

static void	free_coders(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->coder_qnt)
	{
		pthread_mutex_destroy(&table->coders[i].coder_mutex);
		i++;
	}
	free(table->coders);
}

void	free_table(t_table *table)
{
	if (table->dongles)
		free_dongles(table);
	if (table->coders)
		free_coders(table);
	pthread_mutex_destroy(&table->state_mutex);
	pthread_mutex_destroy(&table->log_mutex);
	return ;
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->coder_qnt)
	{
		pthread_join(table->coders[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}
