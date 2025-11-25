/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:37:46 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/25 14:50:55 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* door_rendering.c                                   :+:      :+:    :+:   */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Helper para desenhar pixel (igual ao original) */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static t_img	*get_door_texture(t_game *g, t_door *door)
{
	if (door->state == DOOR_CLOSED)
		return (&g->door_sys.closed_textures[0]);
	else if (door->state == DOOR_OPENING || door->state == DOOR_CLOSING)
		return (&g->door_sys.opening_textures[door->frame]);
	else
		return (&g->door_sys.opening_textures[DOOR_FRAMES - 1]);
}

static int	get_texture_color(t_img *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0) tex_x = 0;
	if (tex_x >= texture->width) tex_x = texture->width - 1;
	if (tex_y < 0) tex_y = 0;
	if (tex_y >= texture->height) tex_y = texture->height - 1;
	
	pixel = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bpp / 8));
	return (*(int *)pixel);
}

/* Função corrigida: Desenha uma coluna vertical específica da porta 
   baseada na posição X da textura calculada no loop principal 
*/
static void	draw_door_stripe_column(t_game *g, int x, double distance, t_img *texture, int tex_x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		tex_y;
	int		d;
	int		color;

	line_height = (int)(WIN_H / distance);
	draw_start = -line_height / 2 + WIN_H / 2;
	if (draw_start < 0) draw_start = 0;
	
	draw_end = line_height / 2 + WIN_H / 2;
	if (draw_end >= WIN_H) draw_end = WIN_H - 1;
	y = draw_start;
	while (y < draw_end)
	{
		d = (y) * 256 - WIN_H * 128 + line_height * 128;
		tex_y = ((d * texture->height) / line_height) / 256;
		color = get_texture_color(texture, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0) 
			my_mlx_pixel_put(&g->screen, x, y, color);
		y++;
	}
}

/* Função Principal Refatorada:
   Trata a porta como um Sprite (Billboard) e itera sobre a largura da tela.
*/
void	render_doors(t_game *g)
{
	int		i;
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	int		tex_x;
	t_img	*texture;

	double dir_x = cos(g->player.angle);
	double dir_y = sin(g->player.angle);
	double plane_x = -dir_y * 0.66;
	double plane_y = dir_x * 0.66;

	i = 0;
	while (i < g->door_sys.door_count)
	{
		//Calcular posição relativa ao jogador
		sprite_x = g->door_sys.doors[i].x + 0.5 - g->player.x;
		sprite_y = g->door_sys.doors[i].y + 0.5 - g->player.y;
		inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
		transform_x = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
		transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y);

		if (transform_y > 0)
		{
			sprite_screen_x = (int)((WIN_W / 2) * (1 + transform_x / transform_y));

			sprite_height = abs((int)(WIN_H / transform_y));
			sprite_width = abs((int)(WIN_H / transform_y));
			draw_start_x = -sprite_width / 2 + sprite_screen_x;
			if (draw_start_x < 0) 
				draw_start_x = 0;
			draw_end_x = sprite_width / 2 + sprite_screen_x;
			if (draw_end_x >= WIN_W) 
				draw_end_x = WIN_W - 1;
			texture = get_door_texture(g, &g->door_sys.doors[i]);
			stripe = draw_start_x;
			while (stripe < draw_end_x)
			{
				tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * texture->width / sprite_width) / 256;
				if (transform_y < g->z_buffer[stripe])
					draw_door_stripe_column(g, stripe, transform_y, texture, tex_x);
				stripe++;
			}
		}
		i++;
	}
}
