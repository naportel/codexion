/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:39:06 by marvin            #+#    #+#             */
/*   Updated: 2026/07/01 15:39:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int init_heap(t_heap *heap, int capacity)
{
    heap->data = malloc(sizeof(t_coder *) * capacity);
    if (!heap->data)
        return (0);
    heap->size = 0;
    heap->capacity = capacity;
    return (1);
}
