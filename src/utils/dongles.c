/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:05:13 by naportel          #+#    #+#             */
/*   Updated: 2026/08/14 15:16:04 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	acquire_dongle(t_coder *coder, t_dongle *dongle)
{
	long	sleep_time;

	pthread_mutex_lock(&dongle->mutex);
	heap_push(&dongle->heap, coder, coder->table->scheduler);
	while (dongle->heap.data[0] != coder || dongle->holder != NULL
		|| get_time() < dongle->available_at)
	{
		if (dongle->holder == NULL && dongle->heap.data[0] == coder)
		{
			sleep_time = (dongle->available_at - get_time()) * 1000;
			if (sleep_time > 0)
			{
				pthread_mutex_unlock(&dongle->mutex);
				usleep(sleep_time);
				pthread_mutex_lock(&dongle->mutex);
			}
		}
		else
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	dongle->holder = coder;
	heap_pop(&dongle->heap, coder->table->scheduler);
	print_log(coder, "has taken a dongle", 0);
	pthread_mutex_unlock(&dongle->mutex);
}

static void	release_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	if (dongle->holder == coder)
	{
		dongle->holder = NULL;
		dongle->available_at = get_time() + coder->table->dongle_cooldown;
		pthread_cond_broadcast(&dongle->cond);
	}
	print_log(coder, "has released a dongle", 0);
	pthread_mutex_unlock(&dongle->mutex);
}

void	lock_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

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
	acquire_dongle(coder, first);
	acquire_dongle(coder, second);
	return ;
}

void	unlock_dongles(t_coder *coder)
{
	release_dongle(coder, coder->left_dongle);
	release_dongle(coder, coder->right_dongle);
	return ;
}
