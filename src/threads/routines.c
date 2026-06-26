/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:01:23 by naportel          #+#    #+#             */
/*   Updated: 2026/05/27 15:01:25 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	evaluate_coders(t_table *t)
{
	int	i;
	int	all_done;

	i = 0;
	all_done = 1;
	while (i < t->coder_qnt)
	{
		pthread_mutex_lock(&t->coders[i].coder_mutex);
		if (get_current_time() - t->coders[i].last_comp > t->burnout)
		{
			print_log(&t->coders[i], "burned out");
			pthread_mutex_unlock(&t->coders[i].coder_mutex);
			return (0);
		}
		if (t->comps_min > 0 && t->coders[i].comps_done < t->comps_min)
			all_done = 0;
		pthread_mutex_unlock(&t->coders[i].coder_mutex);
		i++;
	}
	if (t->compiles_needed > 0 && all_done)
		return (0);
	return (1);
}

int	check_simulation(t_table *table)
{
	pthread_mutex_lock(&table->state_mutex);
	if (!table->simulation_running)
	{
		pthread_mutex_unlock(&table->state_mutex);
		return (0);
	}
	pthread_mutex_unlock(&table->state_mutex);
	if (!evaluate_coders(table))
	{
		pthread_mutex_lock(&table->state_mutex);
		table->simulation_running = 0;
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
	if (table->simulation_running)
	{
		print_log(coder, "is compiling");
		usleep(table->compile_time * 1000);
		pthread_mutex_lock(&coder->coder_mutex);
		coder->last_comp = get_current_time();
		coder->comps_done++;
		pthread_mutex_unlock(&coder->coder_mutex);
		print_log(coder, "finished compiling");
	}
	return (NULL);
}

void	*monitor_routine(void *table)
{
	(t_table *)table;
	while (check_simulation((t_table *)table))
		usleep(1000);
	return (NULL);
}
