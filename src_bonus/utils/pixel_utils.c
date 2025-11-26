/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:30:55 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/26 14:39:39 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int		is_inside_circle(int x, int y, int *center, int radius);
int		calc_pixel_color(t_game *g, int dx, int dy);

void	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel_to_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	put_map_pixel(t_game *g, int sx, int sy)
{
	int	center[2];
	int	dx;
	int	dy;
	int	color;

	center[0] = MINIMAP_X;
	center[1] = MINIMAP_Y;
	if (is_inside_circle(sx, sy, center, MINIMAP_RADIUS))
	{
		dx = sx - center[0];
		dy = sy - center[1];
		color = calc_pixel_color(g, dx, dy);
		put_pixel_to_img(&g->screen, sx, sy, color);
	}
}

/* Desenhar pixel (igual ao original) */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
