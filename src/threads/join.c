/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:42:38 by naportel          #+#    #+#             */
/*   Updated: 2026/08/10 12:26:55 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
