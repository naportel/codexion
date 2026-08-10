/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printlog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 12:25:16 by naportel          #+#    #+#             */
/*   Updated: 2026/08/10 12:25:54 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_log(t_coder *coder, char *msg)
{
	t_table	*table;
	long	time;

	table = coder->table;
	pthread_mutex_lock(&table->log_mutex);
	time = get_current_time() - table->start_time;
	printf("%ld %d %s\n", time, coder->id + 1, msg);
	pthread_mutex_unlock(&table->log_mutex);
}
