/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:05:13 by naportel          #+#    #+#             */
/*   Updated: 2026/08/10 12:34:08 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	lock_dongles(t_coder *coder)
{
    t_dongle *first;
    t_dongle *second;
    
    if (coder->left_dongle < coder->right_dongle)
    {
        first = coder->left_dongle;
        second = coder->right_dongle;
    }
    else
    {
        first = coder->right_dongle;
        second = coder->left_dongle;
    }
	pthread_mutex_lock(&first->mutex);
	print_log(coder, "has taken a dongle");
	pthread_mutex_lock(&second->mutex);
	print_log(coder, "has taken a dongle");
	return ;
}

void	unlock_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_unlock(&coder->right_dongle->mutex);
	return ;
}
