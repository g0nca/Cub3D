/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_los.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:40:08 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/24 11:48:32 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_ray_steps(t_ray_vars *r, double x0, double y0)
{
	if (r->dx < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (x0 - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - x0) * r->delta_dist_x;
	}
	if (r->dy < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (y0 - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - y0) * r->delta_dist_y;
	}
}

static int	perform_dda(t_game *g, t_ray_vars *r, double dist_target)
{
	while (1)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			if (r->side_dist_x - r->delta_dist_x >= dist_target)
				return (1);
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			if (r->side_dist_y - r->delta_dist_y >= dist_target)
				return (1);
		}
		if (r->map_y < 0 || r->map_x < 0 || !g->map.grid[r->map_y])
			return (0);
		if (r->map_x >= (int)ft_strlen(g->map.grid[r->map_y]))
			return (0);
		if (g->map.grid[r->map_y][r->map_x] == '1')
			return (0);
	}
}

int	is_line_of_sight_clear(t_game *g, double x0, double y0, double x1, double y1)
{
	t_ray_vars	r;
	double		dist;

	r.dx = x1 - x0;
	r.dy = y1 - y0;
	dist = sqrt(r.dx * r.dx + r.dy * r.dy);
	if (dist <= 0.0)
		return (1);
	r.map_x = (int)floor(x0);
	r.map_y = (int)floor(y0);
	r.delta_dist_x = (r.dx == 0) ? 1e30 : fabs(1.0 / (r.dx / dist));
	r.delta_dist_y = (r.dy == 0) ? 1e30 : fabs(1.0 / (r.dy / dist));
	init_ray_steps(&r, x0, y0);
	return (perform_dda(g, &r, dist));
}

static int	check_wall_col(t_game *g, double fx, double fy, int tx, int ty)
{
	double	closest_x;
	double	closest_y;
	double	dx;
	double	dy;

	if (g->map.grid[ty][tx] == '1')
	{
		closest_x = fx;
		if (closest_x < (double)tx)
			closest_x = (double)tx;
		if (closest_x > (double)(tx + 1))
			closest_x = (double)(tx + 1);
		closest_y = fy;
		if (closest_y < (double)ty)
			closest_y = (double)ty;
		if (closest_y > (double)(ty + 1))
			closest_y = (double)(ty + 1);
		dx = fx - closest_x;
		dy = fy - closest_y;
		if (sqrt(dx * dx + dy * dy) < ENEMY_SIZE)
			return (1);
	}
	return (0);
}

int	is_walkable_at(t_game *g, double fx, double fy)
{
	int	tx;
	int	ty;
	int	y_limit;
	int	x_limit;

	y_limit = (int)floor(fy + ENEMY_SIZE);
	x_limit = (int)floor(fx + ENEMY_SIZE);
	ty = (int)floor(fy - ENEMY_SIZE);
	while (ty <= y_limit)
	{
		if (ty < 0 || !g->map.grid[ty])
			return (0);
		tx = (int)floor(fx - ENEMY_SIZE);
		while (tx <= x_limit)
		{
			if (tx < 0 || tx >= (int)ft_strlen(g->map.grid[ty]))
				return (0);
			if (check_wall_col(g, fx, fy, tx, ty))
				return (0);
			tx++;
		}
		ty++;
	}
	return (1);
}
