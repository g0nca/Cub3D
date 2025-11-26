/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_all_sprites.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:56:00 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:29:45 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	collect_door_sprites(t_game *g, t_unified_sprite *sprites, int *cnt);
void	collect_enemy_sprites(t_game *g, t_unified_sprite *sprites, int *cnt);
int		compare_sprites(const void *a, const void *b);

static t_img	*get_spr_texture(t_game *g, t_unified_sprite *s)
{
	t_door	*d;
	t_enemy	*e;

	if (s->type == SPRITE_DOOR)
	{
		d = &g->door_sys.doors[s->index];
		if (d->state == DOOR_CLOSED)
			return (&g->door_sys.closed_textures[0]);
		if (d->state == DOOR_OPENING || d->state == DOOR_CLOSING)
			return (&g->door_sys.opening_textures[d->frame]);
		return (&g->door_sys.opening_textures[DOOR_FRAMES - 1]);
	}
	e = &g->enemy_sys.enemies[s->index];
	return (&g->enemy_sys.enemy_textures[e->enemy_type][e->current_frame]);
}

static void	calc_spr_dims(t_game *g, t_unified_sprite *s, t_spr_calc *c)
{
	double	pos[2];
	double	dir[2];
	double	plane[2];
	double	trans_x;

	pos[0] = s->x - g->player.x;
	pos[1] = s->y - g->player.y;
	dir[0] = cos(g->player.angle);
	dir[1] = sin(g->player.angle);
	plane[0] = -dir[1] * 0.66;
	plane[1] = dir[0] * 0.66;
	c->inv_det = 1.0 / (plane[0] * dir[1] - dir[0] * plane[1]);
	trans_x = c->inv_det * (dir[1] * pos[0] - dir[0] * pos[1]);
	c->transform_y = c->inv_det * (-plane[1] * pos[0] + plane[0] * pos[1]);
	c->screen_x = (int)((WIN_W / 2) * (1 + trans_x / c->transform_y));
	c->width = abs((int)(WIN_H / c->transform_y));
	c->start_x = -c->width / 2 + c->screen_x;
	if (c->start_x < 0)
		c->start_x = 0;
	c->end_x = c->width / 2 + c->screen_x;
	if (c->end_x >= WIN_W)
		c->end_x = WIN_W - 1;
}

static void	draw_spr_col(t_game *g, t_spr_calc *c, int x, int tex_x)
{
	int		y;
	int		d;
	int		tex_y;
	int		color;
	int		line_h;

	line_h = (int)(WIN_H / c->transform_y);
	y = -line_h / 2 + WIN_H / 2;
	if (y < 0)
		y = 0;
	while (y < line_h / 2 + WIN_H / 2 && y < WIN_H)
	{
		d = y * 256 - WIN_H * 128 + line_h * 128;
		tex_y = ((d * c->tex->height) / line_h) / 256;
		if (tex_y >= 0 && tex_y < c->tex->height)
		{
			color = *(int *)(c->tex->addr + (tex_y * c->tex->line_len
						+ tex_x * (c->tex->bpp / 8)));
			if ((color & 0x00FFFFFF) != 0)
				my_mlx_pixel_put(&g->screen, x, y, color);
		}
		y++;
	}
}

static void	render_sprite_loop(t_game *g, t_spr_calc *c)
{
	int	stripe;
	int	tex_x;

	stripe = c->start_x;
	while (stripe < c->end_x)
	{
		tex_x = (int)(256 * (stripe - (-c->width / 2 + c->screen_x))
				* c->tex->width / c->width) / 256;
		if (c->transform_y > 0 && c->transform_y < g->z_buffer[stripe])
			draw_spr_col(g, c, stripe, tex_x);
		stripe++;
	}
}

void	render_all_sprites(t_game *g)
{
	t_unified_sprite	sprites[MAX_ENEMIES + MAX_DOORS];
	int					cnt;
	int					i;
	t_spr_calc			c;

	cnt = 0;
	collect_enemy_sprites(g, sprites, &cnt);
	collect_door_sprites(g, sprites, &cnt);
	qsort(sprites, cnt, sizeof(t_unified_sprite), compare_sprites);
	i = 0;
	while (i < cnt)
	{
		calc_spr_dims(g, &sprites[i], &c);
		if (c.transform_y > 0)
		{
			c.tex = get_spr_texture(g, &sprites[i]);
			render_sprite_loop(g, &c);
		}
		i++;
	}
}
