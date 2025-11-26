/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:40:47 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:13 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_walkable_at(t_game *g, double fx, double fy);

static void	update_enemy_animation(t_enemy *enemy)
{
	long	current_time;

	current_time = get_current_time_ms();
	if (current_time - enemy->last_frame_time >= ENEMY_ANIM_SPEED)
	{
		enemy->last_frame_time = current_time;
		enemy->current_frame++;
		if (enemy->current_frame >= FRAMES_PER_ENEMY)
			enemy->current_frame = 0;
	}
}

static void	apply_enemy_movement(t_game *g, t_enemy *e,
	double step_x, double step_y)
{
	double	try_x;
	double	try_y;

	try_x = e->x + step_x;
	try_y = e->y + step_y;
	if (is_walkable_at(g, try_x, try_y))
	{
		e->x = try_x;
		e->y = try_y;
	}
	else
	{
		if (is_walkable_at(g, e->x + step_x, e->y))
			e->x += step_x;
		if (is_walkable_at(g, e->x, e->y + step_y))
			e->y += step_y;
	}
}

static void	process_enemy_logic(t_game *g, int i)
{
	double	dx;
	double	dy;
	double	dist;

	update_enemy_animation(&g->enemy_sys.enemies[i]);
	dx = g->player.x - g->enemy_sys.enemies[i].x;
	dy = g->player.y - g->enemy_sys.enemies[i].y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > 0.0001)
	{
		apply_enemy_movement(g, &g->enemy_sys.enemies[i],
			(dx / dist) * ENEMY_SPEED, (dy / dist) * ENEMY_SPEED);
	}
}

void	update_enemies(t_game *g)
{
	int	i;

	if (g->enemy_sys.game_over)
		return ;
	i = 0;
	while (i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
			process_enemy_logic(g, i);
		i++;
	}
	check_enemy_collision(g);
}
