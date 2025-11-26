/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:12:14 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:29:38 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	get_door_at_position(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->door_sys.door_count)
	{
		if (g->door_sys.doors[i].x == x && g->door_sys.doors[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

/* Verifica se uma porta está bloqueando o movimento */
int	is_door_blocking(t_game *g, int x, int y)
{
	int	door_idx;

	door_idx = get_door_at_position(g, x, y);
	if (door_idx == -1)
		return (0);
	return (g->door_sys.doors[door_idx].state == DOOR_CLOSED
		|| g->door_sys.doors[door_idx].state == DOOR_CLOSING);
}
