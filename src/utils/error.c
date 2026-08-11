/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naportel <naportel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:29:18 by naportel          #+#    #+#             */
/*   Updated: 2026/08/11 13:54:14 by naportel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	error(char *msg)
{
	if (*msg)
	{
		write(2, "Error: ", 7);
		write(2, msg, ft_strlen(msg));
	}
	write(2, "\n", 1);
	return (0);
}

static int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
