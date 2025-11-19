/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_spawn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:29:42 by andrade           #+#    #+#             */
/*   Updated: 2025/11/19 12:16:40 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * Verifica se uma posição é válida para spawn
 * - Não pode ser parede
 * - Não pode estar muito perto do jogador (mínimo 3.0 unidades)
 * - Não pode estar em cima de outro inimigo
 */
int	is_valid_spawn_position(t_game *g, double x, double y)
{
	int		map_x;
	int		map_y;
	double	dist_to_player;
	int		i;

	// Verifica limites do mapa
	map_x = (int)x;
	map_y = (int)y;
	
	if (map_y < 0 || map_x < 0 || !g->map.grid[map_y])
		return (0);
	if (map_x >= (int)ft_strlen(g->map.grid[map_y]))
		return (0);
	
	// Verifica se é parede
	if (g->map.grid[map_y][map_x] == '1')
		return (0);
	
	// Verifica distância ao jogador
	dist_to_player = sqrt(pow(x - g->player.x, 2) + pow(y - g->player.y, 2));
	if (dist_to_player < 1.5)
		return (0);
	
	// Verifica se está em cima de outro inimigo
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

	// Conta dimensões do mapa
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
	printf("posicao invalida\n");
	return (0);
}

/**
 * Spawna um único inimigo
 */
static int	spawn_single_enemy(t_game *g, int index)
{
	double	spawn_x;
	double	spawn_y;
	int		asset_id;

	if (!find_random_spawn_position(g, &spawn_x, &spawn_y))
		return (0);
    
	// Escolhe asset aleatório que foi carregado com sucesso
	asset_id = rand() % ENEMY_ASSETS;
	int attempts = 0;
	while (attempts < ENEMY_ASSETS && (!g->enemy_sys.enemy_textures[asset_id].img ||
			!g->enemy_sys.enemy_textures[asset_id].addr))
	{
		asset_id = (asset_id + 1) % ENEMY_ASSETS;
		attempts++;
	}
	if (attempts >= ENEMY_ASSETS)
		return (0);
	
	// Configura inimigo
	g->enemy_sys.enemies[index].x = spawn_x;
	g->enemy_sys.enemies[index].y = spawn_y;
	g->enemy_sys.enemies[index].asset_id = asset_id;
	g->enemy_sys.enemies[index].active = 1;
	g->enemy_sys.enemies[index].texture = g->enemy_sys.enemy_textures[asset_id];
	
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
	int	i;
	int attempts;

	tile_count = count_floor_tiles(g);
	target_enemies = get_enemy_count_by_tiles(tile_count);
	if (target_enemies == 0)
	{
		printf("Map too small for enemies\n");
		return;
	}
	attempts = 0;
	spawned = 0;
	i = 0;
	while (spawned < target_enemies && spawned < MAX_ENEMIES && attempts < 1000)
		{
			if (spawn_single_enemy(g, spawned)) 
			{
				printf("Enemy %d spawned successfully\n", spawned);
				spawned++;
				attempts = 0;
			}
			else
			{
				attempts++;
				printf("Tentativa falhada, tentando novamente...\n");
			}
		}
		g->enemy_sys.enemy_count = spawned;
		printf("Total de inimigos spawnados: %d\n", spawned);
}
	
