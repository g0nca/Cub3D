/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:21:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:31:15 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"
/*
** Recebe 'center' como array: center[0] = cx, center[1] = cy
** Reduz argumentos de 5 para 4.
*/
int	is_inside_circle(int x, int y, int *center, int radius)
{
	int	dx;
	int	dy;

	dx = x - center[0];
	dy = y - center[1];
	return (dx * dx + dy * dy <= radius * radius);
}

static int	get_map_tile(t_game *g, int map_x, int map_y)
{
	int		rows;
	char	tile;

	if (map_y < 0 || map_x < 0)
		return (1);
	rows = 0;
	while (g->map.grid[rows])
		rows++;
	if (map_y >= rows)
		return (1);
	if (map_x >= (int)ft_strlen(g->map.grid[map_y]))
		return (1);
	tile = g->map.grid[map_y][map_x];
	if (tile == '1' || tile == ' ' || tile == '\t')
		return (1);
	return (g->map.grid[map_y][map_x] == '1');
}

int	get_minimap_color(t_game *g, double world_x, double world_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)world_x;
	map_y = (int)world_y;
	if (get_map_tile(g, map_x, map_y))
		return (0x333333);
	return (0xCCCCCC);
}

/*
** Variável 'r' removida (substituída por 2) para manter apenas 4 variáveis.
*/
void	draw_enemy_marker(t_game *g, int cx, int cy, int color)
{
	int	x;
	int	y;
	int	px;
	int	py;

	x = -2;
	while (x <= 2)
	{
		y = -2;
		while (y <= 2)
		{
			if (x * x + y * y <= 4)
			{
				px = cx + x;
				py = cy + y;
				if (px >= 0 && px < WIN_W && py >= 0 && py < WIN_H)
					put_pixel_to_img(&g->screen, px, py, color);
			}
			y++;
		}
		x++;
	}
}
