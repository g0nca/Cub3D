/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_weapon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:01:46 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/24 12:35:13 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Helper: Processa uma linha horizontal (eixo X) da imagem escalada */
static void	draw_scaled_line(t_img *dest, t_img *src, t_scale_ctx *c, int y_dest)
{
	int				x_dest;
	int				x_src;
	int				y_src;
	unsigned int	color;
	char			*pixel;

	y_src = (int)floor(y_dest * c->s_y);
	if (y_src < 0 || y_src >= src->height)
		return ;
	x_dest = 0;
	while (x_dest < c->w)
	{
		x_src = (int)floor(x_dest * c->s_x);
		if (x_src >= 0 && x_src < src->width)
		{
			pixel = src->addr + (y_src * src->line_len + x_src * (src->bpp / 8));
			color = *(unsigned int *)pixel;
			if (!is_transparent(color))
				put_pixel_to_img(dest, x_dest + c->x_off,
					y_dest + c->y_off, color);
		}
		x_dest++;
	}
}

static void	scale_and_copy_img_to_buffer(t_img *dest, t_img *src,
			int x_off, int y_off, int w, int h)
{
	t_scale_ctx	ctx;
	int			y_dest;

	if (!src || !dest)
		return ;
	ctx.s_x = (double)src->width / w;
	ctx.s_y = (double)src->height / h;
	ctx.x_off = x_off;
	ctx.y_off = y_off;
	ctx.w = w;
	ctx.h = h;
	y_dest = 0;
	while (y_dest < h)
	{
		draw_scaled_line(dest, src, &ctx, y_dest);
		y_dest++;
	}
}

void	render_weapon(t_game *game)
{
	t_img	*tex;
	int		s_w;
	int		s_h;
	int		x;
	int		y;

	tex = &game->weapon.textures[game->weapon.current_frame];
	if (!tex->img)
		return ;
	s_w = (int)(WIN_W * 0.4);
	s_h = (int)(tex->height * ((double)s_w / tex->width));
	x = WIN_W / 2 - s_w / 2;
	y = WIN_H - s_h + 20;
	scale_and_copy_img_to_buffer(&game->screen, tex, x, y, s_w, s_h);
}

void	handle_shoot(t_game *game)
{
	if (game->weapon.is_firing)
		return ;
	game->weapon.is_firing = 1;
	game->weapon.current_frame = 1;
	game->weapon.last_frame_time = get_current_time_ms();
	check_enemy_hit(game);
}