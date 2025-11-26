/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:35 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:31:23 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_wall_at(t_game *g, int x, int y)
{
	if (y < 0 || x < 0)
		return (1);
	if (!g->map.grid[y])
		return (1);
	if (x >= (int)ft_strlen(g->map.grid[y]))
		return (1);
	return (g->map.grid[y][x] == '1');
}

/*
    Realiza todos os cálculos geométricos
    e de textura antes do loop de desenho
*/
static void	calc_wall_info(t_game *g, t_ray *ray, t_wall_ctx *ctx)
{
	double	corrected_dist;

	corrected_dist = ray->distance * cos(ray->ray_angle - g->player.angle);
	if (corrected_dist < 0.0001)
		corrected_dist = 0.0001;
	ctx->wall_height = (int)((double)WIN_H / corrected_dist);
	ctx->draw_start = (WIN_H - ctx->wall_height) / 2;
	ctx->draw_end = ctx->draw_start + ctx->wall_height;
	if (ctx->draw_start < 0)
		ctx->draw_start = 0;
	if (ctx->draw_end >= WIN_H)
		ctx->draw_end = WIN_H - 1;
	ctx->tex = get_texture(g, ray, ray->ray_angle);
	ctx->tex_x = (int)(ray->wall_x * (double)ctx->tex->width);
	if (ctx->tex_x < 0)
		ctx->tex_x = 0;
	if (ctx->tex_x >= ctx->tex->width)
		ctx->tex_x = ctx->tex->width - 1;
	ctx->step = (double)ctx->tex->height / (double)ctx->wall_height;
	ctx->tex_pos = (ctx->draw_start - (WIN_H - ctx->wall_height) / 2.0)
		* ctx->step;
}

/* Loop específico para desenhar os pixels da textura da parede */
static void	draw_wall_pixels(t_game *g, int x, t_wall_ctx *c)
{
	int	y;
	int	tex_y;
	int	color;

	y = c->draw_start;
	while (y < c->draw_end)
	{
		y++;
		tex_y = (int)c->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= c->tex->height)
			tex_y = c->tex->height - 1;
		color = *(int *)(c->tex->addr + (tex_y * c->tex->line_len
					+ c->tex_x * (c->tex->bpp / 8)));
		put_pixel_to_img(&g->screen, x, y, color);
		c->tex_pos += c->step;
	}
}

/* Função principal orquestradora */
void	draw_wall_stripe(t_game *g, int x, t_ray *ray)
{
	t_wall_ctx	ctx;
	int			y;

	calc_wall_info(g, ray, &ctx);
	y = 0;
	while (y < ctx.draw_start)
	{
		y++;
		put_pixel_to_img(&g->screen, x, y, get_ceiling_color(g));
	}
	draw_wall_pixels(g, x, &ctx);
	y = ctx.draw_end;
	while (y < WIN_H)
	{
		y++;
		put_pixel_to_img(&g->screen, x, y, get_floor_color(g));
	}
}
