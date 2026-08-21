/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:29:45 by naportel          #+#    #+#             */
/*   Updated: 2026/08/21 13:59:36 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	coder_compile(t_coder *coder)
{
	print_log(coder, "is compiling", 0);
	update_last_comp(coder);
	usleep(coder->table->comp_time * 1000);
	pthread_mutex_lock(&coder->coder_mutex);
	coder->comps_done++;
	pthread_mutex_unlock(&coder->coder_mutex);
	return ;
}

void	print_log(t_coder *coder, char *msg, int type)
{
	t_table	*table;
	long	time;

	table = coder->table;
	if (is_running(table) || type == 4)
	{
		pthread_mutex_lock(&table->log_mutex);
		time = get_time() - table->start_time;
		printf("%ld %d %s\n", time, coder->id + 1, msg);
		pthread_mutex_unlock(&table->log_mutex);
		if (type == 1)
			usleep(table->debug_time * 1000);
		else if (type == 2)
			usleep(table->refactor_time * 1000);
	}
	else
		return ;
}
