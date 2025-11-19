/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:28:44 by andrade           #+#    #+#             */
/*   Updated: 2025/11/19 11:11:17 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * Carrega todas as texturas dos inimigos - VERSÃO SIMPLES
 */
void	load_enemy_textures(t_game *g)
{
	char	path[256];
	int		i;
	int		loaded_count;

	i = 0;
	loaded_count = 0;
	while (i < ENEMY_ASSETS)
	{
		snprintf(path, sizeof(path), "assets/enemies/enemy_%d.xpm", i);
		g->enemy_sys.enemy_textures[i].img = mlx_xpm_file_to_image(
			g->mlx, path,
			&g->enemy_sys.enemy_textures[i].width,
			&g->enemy_sys.enemy_textures[i].height);
		
		if (!g->enemy_sys.enemy_textures[i].img)
		{
			g->enemy_sys.enemy_textures[i].addr = NULL;
			g->enemy_sys.enemy_textures[i].bpp = 0;
			g->enemy_sys.enemy_textures[i].line_len = 0;
			g->enemy_sys.enemy_textures[i].endian = 0;
			i++;
			continue;
		}
		loaded_count++;
		g->enemy_sys.enemy_textures[i].addr = mlx_get_data_addr(
			g->enemy_sys.enemy_textures[i].img,
			&g->enemy_sys.enemy_textures[i].bpp,
			&g->enemy_sys.enemy_textures[i].line_len,
			&g->enemy_sys.enemy_textures[i].endian);
		i++;
	}
}

/**
 * Conta o número de tiles '0' (chão) no mapa
 */
int	count_floor_tiles(t_game *g)
{
	int	count;
	int	y;
	int	x;

	count = 0;
	y = 0;
	while (g->map.grid[y])
	{
		x = 0;
		while (g->map.grid[y][x])
		{
			if (g->map.grid[y][x] == '0')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/**
 * Determina quantos inimigos spawnar baseado no número de tiles
 */
int	get_enemy_count_by_tiles(int tile_count)
{
	if (tile_count < 5)
		return (0);
	else if (tile_count <= 15)
		return (1);
	else if (tile_count <= 30)
		return (2);
	else if (tile_count <= 50)
		return (3);
	else if (tile_count <= 75)
		return (4);
	else if (tile_count <= 100)
		return (5);
	else
		return (tile_count / 20);
}

/**
 * Inicializa o sistema de inimigos
 */
void	init_enemy_system(t_game *g)
{
	int	i;

	srand(time(NULL));
	i = 0;
	while (i < MAX_ENEMIES)
	{
		g->enemy_sys.enemies[i].active = 0;
		g->enemy_sys.enemies[i].x = 0.0;
		g->enemy_sys.enemies[i].y = 0.0;
		g->enemy_sys.enemies[i].asset_id = 0;
		i++;
	}
	g->enemy_sys.enemy_count = 0;
	g->enemy_sys.game_over = 0;
	load_enemy_textures(g);
	spawn_enemies(g);
}