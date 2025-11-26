/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_render_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:26:05 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:06 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_transparent(int color)
{
	color = color & 0x00FFFFFF;
	if (color == 0x000000 || color == 0xFF00FF)
		return (1);
	return (0);
}

static void	draw_vertical_stripe(t_game *g, t_img *tex,
	t_draw_vars *v, int stripe)
{
	int	tex_x;
	int	y;
	int	d;
	int	tex_y;
	int	color;

	tex_x = (int)((stripe - (-v->sprite_w / 2 + v->sprite_screen_x))
			* tex->width / v->sprite_w);
	if (tex_x < 0 || tex_x >= tex->width)
		return ;
	y = v->draw_start_y;
	while (y < v->draw_end_y)
	{
		d = (y) * 256 - WIN_H * 128 + v->sprite_h * 128;
		tex_y = ((d * tex->height) / v->sprite_h) / 256;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = *(int *)(tex->addr + (tex_y * tex->line_len
					+ tex_x * (tex->bpp / 8)));
		if (!is_transparent(color))
			put_pixel_to_img(&g->screen, stripe, y, color);
		y++;
	}
}

static void	calc_draw_limits(t_draw_vars *v)
{
	v->sprite_h = abs((int)(WIN_H / v->transform_y));
	v->sprite_w = abs((int)(WIN_H / v->transform_y));
	v->draw_start_y = -v->sprite_h / 2 + WIN_H / 2;
	if (v->draw_start_y < 0)
		v->draw_start_y = 0;
	v->draw_end_y = v->sprite_h / 2 + WIN_H / 2;
	if (v->draw_end_y >= WIN_H)
		v->draw_end_y = WIN_H - 1;
	v->draw_start_x = -v->sprite_w / 2 + v->sprite_screen_x;
	if (v->draw_start_x < 0)
		v->draw_start_x = 0;
	v->draw_end_x = v->sprite_w / 2 + v->sprite_screen_x;
	if (v->draw_end_x >= WIN_W)
		v->draw_end_x = WIN_W - 1;
}

static void	calc_transform(t_game *g, t_enemy *enemy, t_draw_vars *v)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	dir_x;
	double	dir_y;

	sprite_x = enemy->x - g->player.x;
	sprite_y = enemy->y - g->player.y;
	dir_x = cos(g->player.angle);
	dir_y = sin(g->player.angle);
	inv_det = 1.0 / ((-dir_y * 0.66) * dir_y - dir_x * (dir_x * 0.66));
	v->transform_y = inv_det * (-(dir_x * 0.66) * sprite_x
			+ (-dir_y * 0.66) * sprite_y);
	v->sprite_screen_x = (int)((WIN_W / 2) * (1 + (inv_det
					* (dir_y * sprite_x - dir_x * sprite_y))
				/ v->transform_y));
}

void	render_sprite_projection(t_game *g, t_enemy *enemy, t_img *tex)
{
	t_draw_vars	v;
	int			stripe;

	calc_transform(g, enemy, &v);
	if (v.transform_y <= 0.0)
		return ;
	calc_draw_limits(&v);
	stripe = v.draw_start_x;
	while (stripe < v.draw_end_x)
	{
		if (stripe >= 0 && stripe < WIN_W)
		{
			if (v.transform_y < g->z_buffer[stripe])
				draw_vertical_stripe(g, tex, &v, stripe);
		}
		stripe++;
	}
}
