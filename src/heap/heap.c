/* ************************************************************************** */
/*																			  */
/*														:::	  ::::::::        */
/*   heap.c											 :+:	  :+:	:+:       */
/*													+:+ +:+		 +:+	      */
/*   By: naportel <naportel@student.42.fr>		  +#+  +:+	   +#+		      */
/*												+#+#+#+#+#+   +#+		      */
/*   Created: 2026/06/22 15:28:21 by naportel		  #+#	#+#			      */
/*   Updated: 2026/06/26 14:54:07 by naportel		 ###   ########.fr	      */
/*	   																	      */
/* ************************************************************************** */

#include "codexion.h"

int	go_first(t_coder *a, t_coder *b, t_scheduler scheduler)
{
	long	deadline_a;
	long	deadline_b;

	if (scheduler == fifo)
	{
		if (a->last_comp < b->last_comp)
			return (1);
		else
			return (2);
	}
	else if (scheduler == edf)
	{
		deadline_a = a->last_comp + a->table->burnout;
		deadline_b = b->last_comp + b->table->burnout;
		if (deadline_a < deadline_b)
			return (1);
		else
			return (2);
	}
}

void	coder_swap(t_coder **a, t_coder **b)
{
	t_coder	*temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void	heap_push(t_heap *heap, t_coder *coder, t_scheduler type)
{
	int current;
	int parent;

	heap->data[heap->size] = coder;
	current = heap->size;
	heap->size++;
	while (current > 0)
	{
		parent = (current - 1) / 2;
		if (go_first(heap->data[current], heap->data[parent], type))
		{
			coder_swap(&heap->data[current], &heap->data[parent]);
			current = parent;
		}
		else
			break;
	}
}

t_coder	heap_pop(t_heap *heap, t_scheduler type)
{
	t_coder	*top_coder;
	int	current;
	int	l;
	int	r;
	int	high;

	top_coder = heap->data[0];
	heap->size--;
	heap->data[0] = heap->data[heap->size];
	current = 0;
	while (1)
	{
		l = 2 * current + 1;
		r = 2 * current + 2;
		high = current;
		if (l < heap->size && go_first(heap->data[l], heap->data[high], type))
			high = l;
		if (r < heap->size && go_first(heap->data[r], heap->data[high], type))
			high = r;
		if (high == current)
			break;
		coder_swap(&heap->data[current], &heap->data[high]);
		current = high;
	}
	return (top_coder);
}
