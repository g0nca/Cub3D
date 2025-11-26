/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_placement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:18:57 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:29:42 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	check_cross_pattern(t_game *g, int x, int y);

/* Helper para contar paredes vizinhas (Reduz variáveis do check_cross) */
int	count_neighbor_walls(t_game *g, int x, int y)
{
	int	walls;

	walls = 0;
	if (y > 0 && g->map.grid[y - 1][x] == '1')
		walls++;
	if (g->map.grid[y + 1] && g->map.grid[y + 1][x] == '1')
		walls++;
	if (x > 0 && g->map.grid[y][x - 1] == '1')
		walls++;
	if (g->map.grid[y][x + 1] == '1')
		walls++;
	return (walls);
}

/* Verifica proximidade com outras portas (Mantém < 25 linhas) */
static int	check_door_distance(t_game *g, int x, int y)
{
	int	i;
	int	dx;
	int	dy;

	i = 0;
	while (i < g->door_sys.door_count)
	{
		dx = abs(g->door_sys.doors[i].x - x);
		dy = abs(g->door_sys.doors[i].y - y);
		if (dx + dy < MIN_DOOR_DISTANCE)
			return (0);
		i++;
	}
	return (1);
}

/* Adiciona uma porta na struct e altera o mapa para 'D' */
static void	add_new_door(t_game *g, int x, int y)
{
	int	i;

	i = g->door_sys.door_count;
	g->door_sys.doors[i].x = x;
	g->door_sys.doors[i].y = y;
	g->door_sys.doors[i].state = DOOR_CLOSED;
	g->door_sys.doors[i].frame = 0;
	g->door_sys.doors[i].anim_counter = 0;
	if (y > 0 && g->map.grid[y - 1][x] == '1')
		g->door_sys.doors[i].is_vertical = 0;
	else
		g->door_sys.doors[i].is_vertical = 1;
	g->map.grid[y][x] = 'D';
	g->door_sys.door_count++;
}

/* Calcula número máximo de portas baseado nos espaços vazios */
static int	calc_max_doors(t_game *g)
{
	int	y;
	int	x;
	int	cnt;

	y = -1;
	cnt = 0;
	while (g->map.grid[++y])
	{
		x = -1;
		while (g->map.grid[y][++x])
			if (g->map.grid[y][x] == '0')
				cnt++;
	}
	cnt = cnt / 15;
	if (cnt > MAX_DOORS)
		return (MAX_DOORS);
	if (cnt < 1)
		return (1);
	return (cnt);
}

/* Função Principal: Loop de tentativa de colocação */
void	place_doors_randomly(t_game *g)
{
	int	y;
	int	x;
	int	max;
	int	tries;

	srand(time(NULL));
	max = calc_max_doors(g);
	tries = 0;
	y = 1;
	while (g->map.grid[y + 1] && g->door_sys.door_count < max && tries < 1000)
	{
		x = 1;
		while (g->map.grid[y][x + 1] && g->door_sys.door_count < max)
		{
			tries++;
			if (check_cross_pattern(g, x, y) && check_door_distance(g, x, y))
				if ((rand() % 100) < 50)
					add_new_door(g, x, y);
			x++;
		}
		y++;
	}
}
