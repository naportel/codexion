/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:01:23 by naportel          #+#    #+#             */
/*   Updated: 2026/08/14 15:13:13 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	evaluate_coders(t_table *table)
{
	int	i;
	int	all_done;

	i = 0;
	all_done = 1;
	while (i < table->coder_qnt)
	{
		pthread_mutex_lock(&table->coders[i].coder_mutex);
		if (get_time() - table->coders[i].last_comp > table->burnout)
		{
			print_log(&table->coders[i], "burned out");
			pthread_mutex_unlock(&table->coders[i].coder_mutex);
			return (0);
		}
		if (table->coders[i].comps_done < table->comps_need)
			all_done = 0;
		pthread_mutex_unlock(&table->coders[i].coder_mutex);
		i++;
	}
	if (all_done)
		return (0);
	return (1);
}

int	check_simulation(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->state_mutex);
	if (!table->simulation_run)
	{
		pthread_mutex_unlock(&table->state_mutex);
		return (0);
	}
	pthread_mutex_unlock(&table->state_mutex);
	if (!evaluate_coders(table))
	{
		pthread_mutex_lock(&table->state_mutex);
		table->simulation_run = 0;
		while (i++ < table->coder_qnt)
		{
			pthread_mutex_lock(&table->dongles[i].mutex);
			table->dongles[i].available_at = get_time();
			pthread_cond_broadcast(&table->dongles[i].cond);
			pthread_mutex_unlock(&table->dongles[i].mutex);
		}
		pthread_mutex_unlock(&table->state_mutex);
		return (0);
	}
	return (1);
}

void	*coder_routine(void *arg)
{
	t_table	*table;
	t_coder	*coder;

	coder = (t_coder *)arg;
	table = coder->table;
	coder->last_comp = get_time();
	while (table->simulation_run)
	{
		lock_dongles(coder);
		if (!check_simulation(table))
		{
			unlock_dongles(coder);
			break ;
		}
		coder_compile(coder);
		unlock_dongles(coder);
		if (!check_simulation(table))
			break ;
		print_log(coder, "is debugging", 1);
		if (!check_simulation(table))
			break ;
		print_log(coder, "is refactoring", 2);
	}
	return (NULL);
}

void	*monitor_routine(void *table)
{
	while (check_simulation((t_table *)table))
		usleep(1000);
	return (NULL);
}
