/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:55 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:28 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	is_wall(t_game *g, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_x < 0 || !g->map.grid[map_y]
		|| map_x >= (int)ft_strlen(g->map.grid[map_y]))
		return (1);
	if (is_door_blocking(g, map_x, map_y))
		return (1);
	return (g->map.grid[map_y][map_x] == '1');
}

void	move_forward_backward(t_game *g, int dir)
{
	double	nx;
	double	ny;

	nx = g->player.x + cos(g->player.angle) * g->player.move_speed * dir;
	ny = g->player.y + sin(g->player.angle) * g->player.move_speed * dir;
	if (!is_wall(g, nx, g->player.y))
		g->player.x = nx;
	if (!is_wall(g, g->player.x, ny))
		g->player.y = ny;
}

void	move_strafe(t_game *g, int dir)
{
	double	nx;
	double	ny;

	nx = g->player.x - sin(g->player.angle) * g->player.move_speed * dir;
	ny = g->player.y + cos(g->player.angle) * g->player.move_speed * dir;
	if (!is_wall(g, nx, g->player.y))
		g->player.x = nx;
	if (!is_wall(g, g->player.x, ny))
		g->player.y = ny;
}
