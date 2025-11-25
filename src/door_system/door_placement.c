/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_placement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 00:00:00 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/25 10:11:19 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Verifica se a posição tem o padrão de cruz (2 paredes, 2 espaços) */
static int	check_cross_pattern(t_game *g, int x, int y)
{
	int		walls;
	int		spaces;
	char	up, down, left, right;

	if (!g->map.grid[y] || x >= (int)ft_strlen(g->map.grid[y]))
		return (0);
	if (g->map.grid[y][x] != '1')
		return (0);

	// Obter células adjacentes
	up = (y > 0) ? g->map.grid[y - 1][x] : '1';
	down = (g->map.grid[y + 1]) ? g->map.grid[y + 1][x] : '1';
	left = (x > 0) ? g->map.grid[y][x - 1] : '1';
	right = g->map.grid[y][x + 1];

	walls = 0;
	spaces = 0;

	if (up == '1')
		walls++;
	else if (up == '0')
		spaces++;

	if (down == '1')
		walls++;
	else if (down == '0')
		spaces++;

	if (left == '1')
		walls++;
	else if (left == '0')
		spaces++;

	if (right == '1')
		walls++;
	else if (right == '0')
		spaces++;

	// Debug: imprimir informação
	if (walls == 2 && spaces == 2)
	{
		printf("Valid door position found at (%d, %d) - U:%c D:%c L:%c R:%c\n",
			x, y, up, down, left, right);
	}

	return (walls == 2 && spaces == 2);
}

/* Verifica se há portas muito próximas */
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

/* Determina se a porta é vertical ou horizontal */
static int	is_door_vertical(t_game *g, int x, int y)
{
	int	vertical_walls;

	vertical_walls = 0;
	if (y > 0 && g->map.grid[y - 1][x] == '1')
		vertical_walls++;
	if (g->map.grid[y + 1] && g->map.grid[y + 1][x] == '1')
		vertical_walls++;
	return (vertical_walls == 2);
}

int	is_valid_door_position(t_game *g, int x, int y)
{
	if (!check_cross_pattern(g, x, y))
		return (0);
	if (!check_door_distance(g, x, y))
		return (0);
	return (1);
}

/* Conta o número de espaços vazios no mapa */
static int	count_empty_spaces(t_game *g)
{
	int	y;
	int	x;
	int	count;

	y = 0;
	count = 0;
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

void	place_doors_randomly(t_game *g)
{
	int	y;
	int	x;
	int	empty_spaces;
	int	max_doors;
	int	attempts;

	srand(time(NULL));
	empty_spaces = count_empty_spaces(g);
	max_doors = empty_spaces / 15;
	if (max_doors > MAX_DOORS)
		max_doors = MAX_DOORS;
	if (max_doors < 1)
		max_doors = 1;

	printf("\n=== DOOR PLACEMENT DEBUG ===\n");
	printf("Empty spaces: %d\n", empty_spaces);
	printf("Max doors to place: %d\n", max_doors);

	attempts = 0;
	y = 1;
	while (g->map.grid[y + 1] && g->door_sys.door_count < max_doors && attempts < 1000)
	{
		x = 1;
		while (g->map.grid[y][x + 1] && g->door_sys.door_count < max_doors)
		{
			attempts++;
			if (is_valid_door_position(g, x, y))
			{
				// 50% de chance de colocar porta em posição válida
				if ((rand() % 100) < 50)
				{
					g->door_sys.doors[g->door_sys.door_count].x = x;
					g->door_sys.doors[g->door_sys.door_count].y = y;
					g->door_sys.doors[g->door_sys.door_count].state = DOOR_CLOSED;
					g->door_sys.doors[g->door_sys.door_count].frame = 0;
					g->door_sys.doors[g->door_sys.door_count].anim_counter = 0;
					g->door_sys.doors[g->door_sys.door_count].is_vertical =
						is_door_vertical(g, x, y);

					printf("Door %d placed at (%d, %d) - Vertical: %d\n",
						g->door_sys.door_count, x, y,
						g->door_sys.doors[g->door_sys.door_count].is_vertical);

					g->door_sys.door_count++;
				}
			}
			x++;
		}
		y++;
	}

	printf("Total doors placed: %d\n", g->door_sys.door_count);
	printf("Total attempts: %d\n", attempts);
	printf("============================\n\n");
}
