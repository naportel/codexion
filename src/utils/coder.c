/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:29:45 by naportel          #+#    #+#             */
/*   Updated: 2026/08/11 11:50:02 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	coder_compile(t_coder *coder)
{
		print_log(coder, "is compiling");
		coder->last_comp = get_current_time();
		usleep(coder->table->comp_time * 1000);
		pthread_mutex_lock(&coder->coder_mutex);
		coder->last_comp = get_current_time();
		coder->comps_done++;
		pthread_mutex_unlock(&coder->coder_mutex);
		print_log(coder, "finished compiling");
		return ;
}
