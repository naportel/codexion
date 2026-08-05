/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:05:13 by naportel          #+#    #+#             */
/*   Updated: 2026/08/05 14:58:33 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	lock_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->dongle_mutex);
	print_log(coder, "has taken a dongle");
	pthread_mutex_lock(&coder->right_dongle->dongle_mutex);
	print_log(coder, "has taken a dongle");
	return ;
}

void	unlock_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left_dongle->dongle_mutex);
	pthread_mutex_unlock(&coder->right_dongle->dongle_mutex);
	return ;
}
