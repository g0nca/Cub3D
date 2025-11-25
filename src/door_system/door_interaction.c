/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_interaction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:38:12 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/25 09:38:20 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	return (g->door_sys.doors[door_idx].state == DOOR_CLOSED ||
			g->door_sys.doors[door_idx].state == DOOR_CLOSING);
}

/* Encontra a porta mais próxima do jogador */
static int	find_nearest_door(t_game *g)
{
	int		i;
	int		nearest;
	double	min_dist;
	double	dist;
	double	dx;
	double	dy;

	i = 0;
	nearest = -1;
	min_dist = 2.0;
	while (i < g->door_sys.door_count)
	{
		dx = g->door_sys.doors[i].x + 0.5 - g->player.x;
		dy = g->door_sys.doors[i].y + 0.5 - g->player.y;
		dist = sqrt(dx * dx + dy * dy);
		if (dist < min_dist)
		{
			min_dist = dist;
			nearest = i;
		}
		i++;
	}
	return (nearest);
}

void	interact_with_door(t_game *g)
{
	int	door_idx;

	door_idx = find_nearest_door(g);
	if (door_idx == -1)
		return ;
	if (g->door_sys.doors[door_idx].state == DOOR_CLOSED)
	{
		g->door_sys.doors[door_idx].state = DOOR_OPENING;
		g->door_sys.doors[door_idx].frame = 0;
		g->door_sys.doors[door_idx].anim_counter = 0;
	}
	else if (g->door_sys.doors[door_idx].state == DOOR_OPEN)
	{
		g->door_sys.doors[door_idx].state = DOOR_CLOSING;
		g->door_sys.doors[door_idx].frame = DOOR_FRAMES - 1;
		g->door_sys.doors[door_idx].anim_counter = 0;
	}
}

void	update_doors(t_game *g)
{
	int	i;

	i = 0;
	while (i < g->door_sys.door_count)
	{
		if (g->door_sys.doors[i].state == DOOR_OPENING)
		{
			g->door_sys.doors[i].anim_counter++;
			if (g->door_sys.doors[i].anim_counter >= DOOR_ANIM_SPEED)
			{
				g->door_sys.doors[i].frame++;
				g->door_sys.doors[i].anim_counter = 0;
				if (g->door_sys.doors[i].frame >= DOOR_FRAMES)
				{
					g->door_sys.doors[i].state = DOOR_OPEN;
					g->door_sys.doors[i].frame = DOOR_FRAMES - 1;
				}
			}
		}
		else if (g->door_sys.doors[i].state == DOOR_CLOSING)
		{
			g->door_sys.doors[i].anim_counter++;
			if (g->door_sys.doors[i].anim_counter >= DOOR_ANIM_SPEED)
			{
				g->door_sys.doors[i].frame--;
				g->door_sys.doors[i].anim_counter = 0;
				if (g->door_sys.doors[i].frame <= 0)
				{
					g->door_sys.doors[i].state = DOOR_CLOSED;
					g->door_sys.doors[i].frame = 0;
				}
			}
		}
		i++;
	}
}
