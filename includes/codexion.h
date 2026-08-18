/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:21:53 by naportel          #+#    #+#             */
/*   Updated: 2026/08/18 11:02:04 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <sys/time.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "struct.h"

int		main(int ac, char **av);

// heap
int		init_heap(t_heap *heap, int capacity);
int		go_first(t_coder *a, t_coder *b, t_scheduler scheduler);
void	coder_swap(t_coder **a, t_coder **b);
void	heap_push(t_heap *heap, t_coder *coder, t_scheduler type);
t_coder	*heap_pop(t_heap *heap, t_scheduler type);

// parsing
int		parse_args(int ac, char **av, t_table *table);
t_table	define_table(char **av, int scheduler);

// threads
int		init_table(t_table *table);
int		init_dongle(t_dongle *dongle);
void	init_coder(t_table *table, t_coder *coder, int id);
int		init_threads(t_table *table);
void	free_table(t_table *table);
void	join_threads(t_table *table);
int		check_simulation(t_table *table);
void	*coder_routine(void *arg);
void	*monitor_routine(void *table);
void	update_last_comp(t_coder *coder);
int		is_running(t_table *table);

// utils
void	coder_compile(t_coder *coder);
int		lock_dongles(t_coder *coder);
void	unlock_dongles(t_coder *coder);
int		error(char *msg);
void	print_log(t_coder *coder, char *msg, int type);
long	get_time(void);

#endif
