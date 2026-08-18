/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 12:21:32 by naportel          #+#    #+#             */
/*   Updated: 2026/08/18 11:48:50 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	update_last_comp(t_coder *coder)
{
	pthread_mutex_lock(&coder->coder_mutex);
	coder->last_comp = get_time();
	pthread_mutex_unlock(&coder->coder_mutex);
}

int	is_running(t_table *table)
{
	int	running;

	pthread_mutex_lock(&table->state_mutex);
	running = table->simulation_run;
	pthread_mutex_unlock(&table->state_mutex);
	return (running);
}
