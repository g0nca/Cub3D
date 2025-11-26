/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_los.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:40:08 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:04 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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

/* Agora recebe arrays para reduzir argumentos:
   start[0] = x0, start[1] = y0
   end[0] = x1, end[1] = y1
*/
int	is_line_of_sight_clear(t_game *g, double *start, double *end)
{
	t_ray_vars	r;
	double		dist;

	r.dx = end[0] - start[0];
	r.dy = end[1] - start[1];
	dist = sqrt(r.dx * r.dx + r.dy * r.dy);
	if (dist <= 0.0)
		return (1);
	r.map_x = (int)floor(start[0]);
	r.map_y = (int)floor(start[1]);
	if (r.dx == 0)
		r.delta_dist_x = 1e30;
	else
		r.delta_dist_x = fabs(1.0 / (r.dx / dist));
	if (r.dy == 0)
		r.delta_dist_y = 1e30;
	else
		r.delta_dist_y = fabs(1.0 / (r.dy / dist));
	init_ray_steps(&r, start[0], start[1]);
	return (perform_dda(g, &r, dist));
}

static int	check_wall_col(t_game *g, t_pos *p, int tx, int ty)
{
	double	c_x;
	double	c_y;

	if (g->map.grid[ty][tx] == '1'
		|| (g->map.grid[ty][tx] == 'D'
		&& g->door_sys.doors->state == DOOR_CLOSED))
	{
		c_x = p->x;
		if (c_x < (double)tx)
			c_x = (double)tx;
		if (c_x > (double)(tx + 1))
			c_x = (double)(tx + 1);
		c_y = p->y;
		if (c_y < (double)ty)
			c_y = (double)ty;
		if (c_y > (double)(ty + 1))
			c_y = (double)(ty + 1);
		if (sqrt(pow(p->x - c_x, 2) + pow(p->y - c_y, 2)) < ENEMY_SIZE)
			return (1);
	}
	return (0);
}

int	is_walkable_at(t_game *g, double fx, double fy)
{
	t_pos	p;
	int		tx;
	int		ty;
	int		limits[2];

	p.x = fx;
	p.y = fy;
	limits[1] = (int)floor(fy + ENEMY_SIZE);
	limits[0] = (int)floor(fx + ENEMY_SIZE);
	ty = (int)floor(fy - ENEMY_SIZE);
	while (ty <= limits[1])
	{
		if (ty < 0 || !g->map.grid[ty])
			return (0);
		tx = (int)floor(fx - ENEMY_SIZE);
		while (tx <= limits[0])
		{
			if ((tx < 0 || tx >= (int)ft_strlen(g->map.grid[ty]))
				|| check_wall_col(g, &p, tx, ty))
				return (0);
			tx++;
		}
		ty++;
	}
	return (1);
}
