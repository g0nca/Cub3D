/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_validate_spawn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:17:58 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:15 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/**
 * Verifica se uma posição é válida para spawn
 */
/* Verifica se as coordenadas estão dentro do mapa e não são uma parede */
static int	check_map_bounds(t_game *g, int map_x, int map_y)
{
	if (map_y < 0 || map_x < 0 || !g->map.grid[map_y])
		return (0);
	if (map_x >= (int)ft_strlen(g->map.grid[map_y]))
		return (0);
	if (g->map.grid[map_y][map_x] == '1')
		return (0);
	return (1);
}

/* Verifica a distância de segurança em relação ao jogador */
static int	check_player_dist(t_game *g, double x, double y)
{
	double	dist;

	dist = sqrt(pow(x - g->player.x, 2) + pow(y - g->player.y, 2));
	if (dist < 1.5)
		return (0);
	return (1);
}

/* Verifica a distância de segurança em relação aos outros inimigos ativos */
static int	check_enemy_dist(t_game *g, double x, double y)
{
	int		i;
	double	dist;

	i = 0;
	while (i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
		{
			dist = sqrt(pow(x - g->enemy_sys.enemies[i].x, 2)
					+ pow(y - g->enemy_sys.enemies[i].y, 2));
			if (dist < 1.0)
				return (0);
		}
		i++;
	}
	return (1);
}

/* Função Principal para validar posicoes para os enimigos */
int	is_valid_spawn_position(t_game *g, double x, double y)
{
	if (!check_map_bounds(g, (int)x, (int)y))
		return (0);
	if (!check_player_dist(g, x, y))
		return (0);
	if (!check_enemy_dist(g, x, y))
		return (0);
	return (1);
}
