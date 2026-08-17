/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:01:42 by naportel          #+#    #+#             */
/*   Updated: 2026/08/14 19:36:43 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_table(t_table *table)
{
	int	i;

	i = 0;
	if (table->dongles)
	{
		while (i < table->coder_qnt)
		{
			free(table->dongles[i].heap.data);
			pthread_mutex_destroy(&table->dongles[i].mutex);
			pthread_cond_destroy(&table->dongles[i].cond);
			i++;
		}
		free(table->dongles);
	}
	if (table->coders)
		free(table->coders);
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
