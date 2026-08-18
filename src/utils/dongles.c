/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:05:13 by naportel          #+#    #+#             */
/*   Updated: 2026/08/18 15:28:13 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	acquire_dongle(t_coder *coder, t_dongle *dongle)
{
	long	now;

	pthread_mutex_lock(&dongle->mutex);
	heap_push(&dongle->heap, coder, coder->table->scheduler);
	while (dongle->holder != coder)
	{
		if (dongle->holder == NULL && dongle->heap.data[0] == coder)
		{
			now = get_time();
			if (now < dongle->available_at)
			{
				pthread_mutex_unlock(&dongle->mutex);
				usleep((dongle->available_at - now) * 1000);
				pthread_mutex_lock(&dongle->mutex);
				continue ;
			}
			dongle->holder = coder;
			heap_pop(&dongle->heap, coder->table->scheduler);
			pthread_mutex_unlock(&dongle->mutex);
			print_log(coder, "has taken a dongle", 0);
			break ;
		}
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
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
	pthread_mutex_unlock(&dongle->mutex);
}

int	lock_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	if (coder->left_dongle == coder->right_dongle || !coder->right_dongle)
		return (0);
	first = coder->left_dongle;
	second = coder->right_dongle;
	if (first > second)
	{
		first = coder->right_dongle;
		second = coder->left_dongle;
	}
	acquire_dongle(coder, first);
	acquire_dongle(coder, second);
	return (1);
}

void	unlock_dongles(t_coder *coder)
{
	if (coder->left_dongle == coder->right_dongle)
		return ;
	release_dongle(coder, coder->left_dongle);
	release_dongle(coder, coder->right_dongle);
	return ;
}
