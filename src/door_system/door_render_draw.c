/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_render_draw.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:23:01 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/25 13:24:14 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_pixels_loop(t_game *g, t_door_render *r, int x, int tex_x)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;
	int	draw_end;

	draw_end = r->h / 2 + WIN_H / 2;
	if (draw_end >= WIN_H)
		draw_end = WIN_H - 1;
	y = -r->h / 2 + WIN_H / 2;
	if (y < 0)
		y = 0;
	while (y < draw_end)
	{
		d = y * 256 - WIN_H * 128 + r->h * 128;
		tex_y = ((d * r->tex->height) / r->h) / 256;
		color = get_texture_color(r->tex, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
			my_mlx_pixel_put(&g->screen, x, y, color);
		y++;
	}
}

/* Recebe a estrutura para evitar passar 5 argumentos */
void	draw_door_stripe_col(t_game *g, t_door_render *r, int x, int tex_x)
{
	draw_pixels_loop(g, r, x, tex_x);
}