/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_enemy_coallision.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:27:41 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:29:52 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	is_line_of_sight_clear(t_game *g, double *start, double *end);
int	is_walkable_at(t_game *g, double fx, double fy);

/* Trata a colisão de um único inimigo */
static void	check_single_collision(t_game *g, int i, double *player_pos)
{
	double	enemy_pos[2];
	double	dist;

	enemy_pos[0] = g->enemy_sys.enemies[i].x;
	enemy_pos[1] = g->enemy_sys.enemies[i].y;
	dist = sqrt(pow(player_pos[0] - enemy_pos[0], 2)
			+ pow(player_pos[1] - enemy_pos[1], 2));
	if (dist < COLLISION_DISTANCE)
	{
		if (is_line_of_sight_clear(g, enemy_pos, player_pos))
		{
			printf("GAME OVER!\n");
			g->enemy_sys.game_over = 1;
		}
	}
}

/* Itera sobre a lista de inimigos */
void	check_enemy_collision(t_game *g)
{
	double	player_pos[2];
	int		i;

	if (g->enemy_sys.game_over)
		return ;
	player_pos[0] = g->player.x;
	player_pos[1] = g->player.y;
	i = -1;
	while (++i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
		{
			check_single_collision(g, i, player_pos);
			if (g->enemy_sys.game_over)
				return ;
		}
	}
}
