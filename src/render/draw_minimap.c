/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:22:32 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/24 12:22:45 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Protótipos de draw_minimap_utils.c */
int		is_inside_circle(int x, int y, int cx, int cy, int radius);
int		get_minimap_color(t_game *g, double world_x, double world_y);
void	draw_enemy_marker(t_game *g, int cx, int cy, int color);

static void	draw_minimap_border(t_game *g)
{
	int	sx;
	int	sy;
	int	dist_sq;

	sy = MINIMAP_Y - MINIMAP_RADIUS - 2;
	while (sy <= MINIMAP_Y + MINIMAP_RADIUS + 2)
	{
		sx = MINIMAP_X - MINIMAP_RADIUS - 2;
		while (sx <= MINIMAP_X + MINIMAP_RADIUS + 2)
		{
			dist_sq = pow(sx - MINIMAP_X, 2) + pow(sy - MINIMAP_Y, 2);
			if (dist_sq <= pow(MINIMAP_RADIUS + 2, 2) && \
				dist_sq >= pow(MINIMAP_RADIUS, 2))
			{
				put_pixel_to_img(&g->screen, sx, sy, 0x000000);
			}
			sx++;
		}
		sy++;
	}
}

static void	put_map_pixel(t_game *g, int sx, int sy)
{
	int		dx;
	int		dy;
	double	wx;
	double	wy;
	int		color;

	if (is_inside_circle(sx, sy, MINIMAP_X, MINIMAP_Y, MINIMAP_RADIUS))
	{
		dx = sx - MINIMAP_X;
		dy = sy - MINIMAP_Y;
		wx = g->player.x + (double)dx / MINIMAP_SCALE;
		wy = g->player.y + (double)dy / MINIMAP_SCALE;
		color = get_minimap_color(g, wx, wy);
		if ((dx * dx + dy * dy) > pow(MINIMAP_RADIUS - 5, 2))
			color = (color >> 1) & 0x7F7F7F;
		put_pixel_to_img(&g->screen, sx, sy, color);
	}
}

static void	draw_map_background(t_game *g)
{
	int	sx;
	int	sy;

	sy = MINIMAP_Y - MINIMAP_RADIUS;
	while (sy <= MINIMAP_Y + MINIMAP_RADIUS)
	{
		sx = MINIMAP_X - MINIMAP_RADIUS;
		while (sx <= MINIMAP_X + MINIMAP_RADIUS)
		{
			put_map_pixel(g, sx, sy);
			sx++;
		}
		sy++;
	}
}

static void	draw_minimap_enemies(t_game *g)
{
	int		i;
	int		mx;
	int		my;

	i = 0;
	while (i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
		{
			mx = MINIMAP_X + (int)((g->enemy_sys.enemies[i].x - g->player.x) \
				* MINIMAP_SCALE);
			my = MINIMAP_Y + (int)((g->enemy_sys.enemies[i].y - g->player.y) \
				* MINIMAP_SCALE);
			if (is_inside_circle(mx, my, MINIMAP_X, MINIMAP_Y, MINIMAP_RADIUS))
				draw_enemy_marker(g, mx, my, 0xFF0000);
		}
		i++;
	}
}

void	draw_minimap(t_game *g)
{
	draw_map_background(g);
	draw_minimap_border(g);
	draw_minimap_enemies(g);
}