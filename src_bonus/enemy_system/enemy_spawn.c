/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:29:42 by andrade           #+#    #+#             */
/*   Updated: 2025/11/26 15:16:24 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/**
 * Encontra uma posição aleatória válida no mapa
 */
static int	find_random_spawn_position(t_game *g, double *x, double *y)
{
	int		attempts;
	int		map_height;
	int		map_width;
	int		rand_x;
	int		rand_y;

	map_height = 0;
	while (g->map.grid[map_height])
		map_height++;
	map_width = g->map.width;
	attempts = 0;
	while (attempts < 100)
	{
		rand_x = rand() % map_width;
		rand_y = rand() % map_height;
		*x = rand_x + 0.5;
		*y = rand_y + 0.5;
		if (is_valid_spawn_position(g, *x, *y))
			return (1);
		attempts++;
	}
	return (0);
}

/**
 * Copia os frames do tipo de inimigo para o inimigo específico
 */
static void	copy_enemy_frames(t_game *g, int enemy_index, int enemy_type)
{
	int	frame;

	frame = 0;
	while (frame < FRAMES_PER_ENEMY)
	{
		g->enemy_sys.enemies[enemy_index].frames[frame]
			= g->enemy_sys.enemy_textures[enemy_type][frame];
		frame++;
	}
}

static int	trying_spawn_enemys(t_game *g, int enemy_type)
{
	int	attempts;

	attempts = 0;
	while (attempts < ENEMY_TYPES)
	{
		enemy_type = (enemy_type + 1) % ENEMY_TYPES;
		if (g->enemy_sys.enemy_textures[enemy_type][0].img &&
				g->enemy_sys.enemy_textures[enemy_type][0].addr)
			break ;
		attempts++;
	}
	return (attempts);
}

/**
 * Spawna um único inimigo
 */
static int	spawn_single_enemy(t_game *g, int index)
{
	double	spawn_x;
	double	spawn_y;
	int		enemy_type;

	if (!find_random_spawn_position(g, &spawn_x, &spawn_y))
		return (0);
	enemy_type = rand() % ENEMY_TYPES;
	if (!g->enemy_sys.enemy_textures[enemy_type][0].img ||
		!g->enemy_sys.enemy_textures[enemy_type][0].addr)
	{
		if (trying_spawn_enemys(g, enemy_type) >= ENEMY_TYPES)
			return (0);
	}
	g->enemy_sys.enemies[index].x = spawn_x;
	g->enemy_sys.enemies[index].y = spawn_y;
	g->enemy_sys.enemies[index].enemy_type = enemy_type;
	g->enemy_sys.enemies[index].active = 1;
	g->enemy_sys.enemies[index].current_frame = 0;
	g->enemy_sys.enemies[index].last_frame_time = get_current_time_ms();
	copy_enemy_frames(g, index, enemy_type);
	return (1);
}

/**
 * Spawna todos os inimigos baseado no número de tiles
 */
void	spawn_enemies(t_game *g)
{
	int	tile_count;
	int	target_enemies;
	int	spawned;
	int	attempts;

	tile_count = count_floor_tiles(g);
	target_enemies = get_enemy_count_by_tiles(tile_count);
	if (target_enemies == 0)
	{
		close_window(g);
		print_error_and_exit_free("No enemies to spawn", 1, g->cub.map);
	}
	attempts = 0;
	spawned = 0;
	while (spawned < target_enemies && spawned < MAX_ENEMIES && attempts < 1000)
	{
		if (spawn_single_enemy(g, spawned))
		{
			spawned++;
			attempts = 0;
		}
		else
			attempts++;
	}
	g->enemy_sys.enemy_count = spawned;
}
