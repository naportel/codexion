/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 14:36:09 by naportel          #+#    #+#             */
/*   Updated: 2026/06/26 15:17:38 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <pthreads.h>

typedef enum e_scheduler
{
	fifo,
	edf
}						t_scheduler;

typedef struct s_heap
{
	t_coder				**data;
	int					size;
	int					capacity;
}						t_heap;

typedef struct s_dongle
{
	pthread_mutex_t		mutex;
	long				available_at;
	t_heap				heap;
}						t_dongle;

typedef struct s_table
{
	int					coder_qnt;
	long				burnout;
	long				comp_time;
	long				debug_time;
	long				refactor_time;
	int					comps_need;
	long				dongle_cooldown;
	t_scheduler			scheduler;
	int					simulation_run;
	long				start_time;
	t_dongle			*dongles;
	struct s_coder		*coders;
	pthread_t			monitor;
	pthread_mutex_t		log_mutex;
	pthread_mutex_t		state_mutex;
}							t_table;

typedef struct s_coder
{
	int					id;
	int					comps_done;
	long				last_comp;
	pthread_t			thread;
	pthread_mutex_t		coder_mutex;
	pthread_mutex_t		*left_dongle;
	pthread_mutex_t		*right_dongle;
	t_table				*table;
}							t_coder;

#endif
