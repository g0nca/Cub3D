/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:29:42 by andrade           #+#    #+#             */
/*   Updated: 2025/11/20 13:02:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * Verifica se uma posição é válida para spawn
 */
int	is_valid_spawn_position(t_game *g, double x, double y)
{
	int		map_x;
	int		map_y;
	double	dist_to_player;
	int		i;

	map_x = (int)x;
	map_y = (int)y;

	if (map_y < 0 || map_x < 0 || !g->map.grid[map_y])
		return (0);
	if (map_x >= (int)ft_strlen(g->map.grid[map_y]))
		return (0);

	if (g->map.grid[map_y][map_x] == '1')
		return (0);

	dist_to_player = sqrt(pow(x - g->player.x, 2) + pow(y - g->player.y, 2));
	if (dist_to_player < 1.5)
		return (0);

	i = 0;
	while (i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
		{
			double dist = sqrt(
				pow(x - g->enemy_sys.enemies[i].x, 2) +
				pow(y - g->enemy_sys.enemies[i].y, 2)
			);
			if (dist < 1.0)
				return (0);
		}
		i++;
	}

	return (1);
}

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
		{
			printf("Posicao Valida\n");
			return (1);
		}
		attempts++;
	}
	return (0);
}

/**
 * Copia os frames do tipo de inimigo para o inimigo específico
 */
static void copy_enemy_frames(t_game *g, int enemy_index, int enemy_type)
{
	int frame;

	frame = 0;
	while (frame < FRAMES_PER_ENEMY)
	{
		g->enemy_sys.enemies[enemy_index].frames[frame] =
			g->enemy_sys.enemy_textures[enemy_type][frame];
		frame++;
	}
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

	// Escolhe tipo aleatório de inimigo (0-4)
	enemy_type = rand() % ENEMY_TYPES;

	// Verifica se pelo menos o primeiro frame deste tipo foi carregado
	if (!g->enemy_sys.enemy_textures[enemy_type][0].img ||
		!g->enemy_sys.enemy_textures[enemy_type][0].addr)
	{
		printf("[DEBUG] Enemy type %d has no valid textures, trying another\n", enemy_type);
		int attempts = 0;
		while (attempts < ENEMY_TYPES)
		{
			enemy_type = (enemy_type + 1) % ENEMY_TYPES;
			if (g->enemy_sys.enemy_textures[enemy_type][0].img &&
				g->enemy_sys.enemy_textures[enemy_type][0].addr)
				break;
			attempts++;
		}
		if (attempts >= ENEMY_TYPES)
			return (0);
	}

	// Configura inimigo
	g->enemy_sys.enemies[index].x = spawn_x;
	g->enemy_sys.enemies[index].y = spawn_y;
	g->enemy_sys.enemies[index].enemy_type = enemy_type;
	g->enemy_sys.enemies[index].active = 1;
	g->enemy_sys.enemies[index].current_frame = 0;
	g->enemy_sys.enemies[index].last_frame_time = get_current_time_ms();

	// Copia os frames para este inimigo
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
	int attempts;

	tile_count = count_floor_tiles(g);
	target_enemies = get_enemy_count_by_tiles(tile_count);
	if (target_enemies == 0)
	{
		close_window(g);
		print_error_and_exit_FREE("No enemies to spawn", 1, g->cub.map);
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
