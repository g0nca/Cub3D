/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 09:37:46 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/25 09:52:05 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Obtém a textura correta para a porta baseado no estado */
static t_img	*get_door_texture(t_game *g, t_door *door)
{
	if (door->state == DOOR_CLOSED)
		return (&g->door_sys.closed_textures[0]);
	else if (door->state == DOOR_OPENING || door->state == DOOR_CLOSING)
		return (&g->door_sys.opening_textures[door->frame]);
	else
		return (&g->door_sys.opening_textures[DOOR_FRAMES - 1]);
}

/* Obtém a cor de um pixel da textura */
static int	get_texture_color(t_img *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0 || tex_x >= texture->width)
		tex_x = 0;
	if (tex_y < 0 || tex_y >= texture->height)
		tex_y = 0;
	pixel = texture->addr + (tex_y * texture->line_len
		+ tex_x * (texture->bpp / 8));
	return (*(int *)pixel);
}

/* Desenha uma coluna vertical da porta */
static void	draw_door_stripe(t_game *g, int x, double distance,
		t_img *texture, double wall_x)
{
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	unsigned int	color;

	wall_height = (int)(WIN_H / distance);
	draw_start = (WIN_H - wall_height) / 2;
	draw_end = (WIN_H + wall_height) / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_H)
		draw_end = WIN_H - 1;
	tex_x = (int)(wall_x * texture->width);
	step = (double)texture->height / wall_height;
	tex_pos = (draw_start - (WIN_H - wall_height) / 2.0) * step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = get_texture_color(texture, tex_x, tex_y);
		if (color != 0xFF000000)
			my_mlx_pixel_put(&g->screen, x, y, color);
		y++;
	}
}

/* Renderiza todas as portas visíveis */
void	render_doors(t_game *g)
{
	int		i;
	double	dx;
	double	dy;
	double	distance;
	double	angle_to_door;
	double	angle_diff;
	int		screen_x;
	double	fov;
	t_img	*texture;
	double	wall_x;

	i = 0;
	fov = M_PI / 3;
	while (i < g->door_sys.door_count)
	{
		dx = g->door_sys.doors[i].x + 0.5 - g->player.x;
		dy = g->door_sys.doors[i].y + 0.5 - g->player.y;
		angle_to_door = atan2(dy, dx);
		angle_diff = angle_to_door - g->player.angle;
		while (angle_diff < -M_PI)
			angle_diff += 2 * M_PI;
		while (angle_diff > M_PI)
			angle_diff -= 2 * M_PI;
		if (fabs(angle_diff) < fov / 2 + 0.1)
		{
			distance = sqrt(dx * dx + dy * dy) * cos(angle_diff);
			screen_x = (int)((angle_diff + fov / 2) * WIN_W / fov);
			if (screen_x >= 0 && screen_x < WIN_W)
			{
				if (distance > 0 && distance < g->z_buffer[screen_x])
				{
					texture = get_door_texture(g, &g->door_sys.doors[i]);
					if (g->door_sys.doors[i].is_vertical)
						wall_x = g->player.y + distance * sin(angle_to_door);
					else
						wall_x = g->player.x + distance * cos(angle_to_door);
					wall_x -= floor(wall_x);
					draw_door_stripe(g, screen_x, distance, texture, wall_x);
				}
			}
		}
		i++;
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
