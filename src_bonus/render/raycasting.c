/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:36 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:31:25 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/* Inicializa direções, deltas e distâncias iniciais (side_dist) */
static void	init_dda(t_game *g, t_dda *d, double angle)
{
	d->map_x = (int)g->player.x;
	d->map_y = (int)g->player.y;
	d->r_dir_x = cos(angle);
	d->r_dir_y = sin(angle);
	d->delta_x = 1e30;
	if (d->r_dir_x != 0)
		d->delta_x = fabs(1 / d->r_dir_x);
	d->delta_y = 1e30;
	if (d->r_dir_y != 0)
		d->delta_y = fabs(1 / d->r_dir_y);
	d->step_x = 1;
	d->side_x = (d->map_x + 1.0 - g->player.x) * d->delta_x;
	if (d->r_dir_x < 0)
	{
		d->step_x = -1;
		d->side_x = (g->player.x - d->map_x) * d->delta_x;
	}
	d->step_y = 1;
	d->side_y = (d->map_y + 1.0 - g->player.y) * d->delta_y;
	if (d->r_dir_y < 0)
	{
		d->step_y = -1;
		d->side_y = (g->player.y - d->map_y) * d->delta_y;
	}
}

/* Executa o loop principal do DDA até encontrar parede */
static void	run_dda_loop(t_game *g, t_dda *d)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (d->side_x < d->side_y)
		{
			d->side_x += d->delta_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_y += d->delta_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (is_wall_at(g, d->map_x, d->map_y))
			hit = 1;
	}
}

/* Função Principal de Raycasting: Faz o DDA e calcula resultados */
static void	cast_ray_dda(t_game *g, t_ray *ray, double angle)
{
	t_dda	d;

	init_dda(g, &d, angle);
	run_dda_loop(g, &d);
	if (d.side == 0)
		ray->distance = (d.side_x - d.delta_x);
	else
		ray->distance = (d.side_y - d.delta_y);
	if (d.side == 0)
		ray->wall_x = g->player.y + ray->distance * d.r_dir_y;
	else
		ray->wall_x = g->player.x + ray->distance * d.r_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->hit_vertical = (d.side == 0);
	ray->ray_angle = angle;
}

/* Seleciona a textura baseada na direção e colisão */
t_img	*get_texture(t_game *g, t_ray *ray, double angle)
{
	if (ray->hit_vertical)
	{
		if (cos(angle) > 0)
			return (&g->textures.east);
		return (&g->textures.west);
	}
	else
	{
		if (sin(angle) > 0)
			return (&g->textures.south);
		return (&g->textures.north);
	}
}

/* Loop principal de renderização da visão 3D */
void	render_3d_view(t_game *g)
{
	double	fov;
	double	ray_angle;
	t_ray	ray;
	int		x;

	fov = M_PI / 3;
	ray_angle = g->player.angle - fov / 2;
	x = 0;
	while (x < WIN_W)
	{
		cast_ray_dda(g, &ray, ray_angle);
		draw_wall_stripe(g, x, &ray);
		if (x >= 0 && x < WIN_W)
			g->z_buffer[x] = ray.distance;
		ray_angle += (fov / WIN_W);
		x++;
	}
}
