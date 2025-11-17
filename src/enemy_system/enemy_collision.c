/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:31:43 by andrade           #+#    #+#             */
/*   Updated: 2025/11/17 09:52:43 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
 * Verifica se há linha de visão direta entre (x0,y0) e (x1,y1).
 * Caminha ao longo do segmento e retorna 1 se não houver paredes entre os pontos.
 */
static int is_line_of_sight_clear(t_game *g, double x0, double y0, double x1, double y1)
{
	/* Use DDA ray cast from (x0,y0) towards (x1,y1). If a wall is hit before
	 * reaching the player position, LOS is blocked. This mirrors the raycaster
	 * approach and avoids sampling gaps.
	 */
	double dx = x1 - x0;
	double dy = y1 - y0;
	double dist_to_target = sqrt(dx * dx + dy * dy);
	if (dist_to_target <= 0.0)
		return (1);

	double ray_dir_x = dx / dist_to_target;
	double ray_dir_y = dy / dist_to_target;

	int map_x = (int)floor(x0);
	int map_y = (int)floor(y0);

	double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
	double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);

	int step_x;
	int step_y;
	double side_dist_x;
	double side_dist_y;

	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (x0 - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - x0) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (y0 - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - y0) * delta_dist_y;
	}

	int hit = 0;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			// distance from origin to this vertical side
			double traveled = side_dist_x - delta_dist_x;
			if (traveled >= dist_to_target)
				return (1);
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			double traveled = side_dist_y - delta_dist_y;
			if (traveled >= dist_to_target)
				return (1);
		}

		if (map_y < 0 || map_x < 0)
			return (0);
		if (!g->map.grid[map_y])
			return (0);
		if (map_x >= (int)ft_strlen(g->map.grid[map_y]))
			return (0);
		if (g->map.grid[map_y][map_x] == '1')
			return (0); // wall blocks LOS
	}

	return (1);
}

/* Helper: verifica se uma posição (double) é caminhável (não parede) */
static int is_walkable_at(t_game *g, double fx, double fy)
{
	/*
	* Use circle-vs-tile collision to prevent clipping through corners.
	* Check all tiles that the enemy's collision circle could overlap.
	*/
	int x0 = (int)floor(fx - ENEMY_SIZE);
	int x1 = (int)floor(fx + ENEMY_SIZE);
	int y0 = (int)floor(fy - ENEMY_SIZE);
	int y1 = (int)floor(fy + ENEMY_SIZE);
	int tx, ty;

	for (ty = y0; ty <= y1; ty++)
	{
		if (ty < 0 || !g->map.grid[ty])
			return (0);
		for (tx = x0; tx <= x1; tx++)
		{
			if (tx < 0 || tx >= (int)ft_strlen(g->map.grid[ty]))
				return (0);
			if (g->map.grid[ty][tx] == '1')
			{
				/* Closest point on the tile rectangle to the circle center */
				double closest_x = fx;
				if (closest_x < (double)tx)
					closest_x = (double)tx;
				if (closest_x > (double)(tx + 1))
					closest_x = (double)(tx + 1);

				double closest_y = fy;
				if (closest_y < (double)ty)
					closest_y = (double)ty;
				if (closest_y > (double)(ty + 1))
					closest_y = (double)(ty + 1);

				double dx = fx - closest_x;
				double dy = fy - closest_y;
				if (sqrt(dx * dx + dy * dy) < ENEMY_SIZE)
					return (0); // collision with wall tile
			}
		}
	}
	return (1);
}

/**
 * Verifica colisão entre jogador e inimigos
 */
void	check_enemy_collision(t_game *g)
{
	int		i;
	double	distance;

	if (g->enemy_sys.game_over)
		return;

	i = 0;
	while (i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
		{
			distance = sqrt(
				pow(g->player.x - g->enemy_sys.enemies[i].x, 2) +
				pow(g->player.y - g->enemy_sys.enemies[i].y, 2)
			);

			if (distance < COLLISION_DISTANCE)
			{
				/* Só mata se houver linha de visão direta (sem paredes entre) */
				if (is_line_of_sight_clear(g,
					g->enemy_sys.enemies[i].x, g->enemy_sys.enemies[i].y,
					g->player.x, g->player.y))
				{
					printf("GAME OVER! Player touched enemy at (%.2f, %.2f)\n",
						g->enemy_sys.enemies[i].x, g->enemy_sys.enemies[i].y);
					g->enemy_sys.game_over = 1;
					return;
				}
			}
		}
		i++;
	}
}

/**
 * Atualiza o sistema de inimigos (chamado a cada frame)
 */
void	update_enemies(t_game *g)
{
	int i;
	double dx;
	double dy;
	double dist;
	double nx;
	double ny;
	double step_x;
	double step_y;
	static time_t last_debug = 0;
	double nearest = 1e9;

	if (g->enemy_sys.game_over)
		return;

	i = 0;
	while (i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
		{
			// Vetor do inimigo até o jogador
			dx = g->player.x - g->enemy_sys.enemies[i].x;
			dy = g->player.y - g->enemy_sys.enemies[i].y;
			dist = sqrt(dx * dx + dy * dy);

			if (dist > 0.0001)
			{
				// Normaliza direção
				nx = dx / dist;
				ny = dy / dist;

				// Movimento proposto
				step_x = nx * ENEMY_SPEED;
				step_y = ny * ENEMY_SPEED;

				/*
				* Melhor estratégia de movimento:
				* - Primeiro tenta mover pelo vetor completo (step_x, step_y).
				* - Se bloqueado, tenta mover separadamente por eixo X e Y.
				*/

				double try_x = g->enemy_sys.enemies[i].x + step_x;
				double try_y = g->enemy_sys.enemies[i].y + step_y;

				if (is_walkable_at(g, try_x, try_y))
				{
					g->enemy_sys.enemies[i].x = try_x;
					g->enemy_sys.enemies[i].y = try_y;
				}
				else
				{
					// Tenta eixo X
					if (is_walkable_at(g, g->enemy_sys.enemies[i].x + step_x, g->enemy_sys.enemies[i].y))
						g->enemy_sys.enemies[i].x += step_x;
					// Tenta eixo Y
					if (is_walkable_at(g, g->enemy_sys.enemies[i].x, g->enemy_sys.enemies[i].y + step_y))
						g->enemy_sys.enemies[i].y += step_y;
				}
			}
		}

		/* track nearest enemy for debug */
		if (g->enemy_sys.enemies[i].active && dist < nearest)
			nearest = dist;
		i++;
	}

	// Verifica colisões com o jogador após mover inimigos
	check_enemy_collision(g);

	/* Debug: print nearest enemy distance once per second */
	if (time(NULL) - last_debug >= 1)
	{
		printf("[DEBUG] nearest enemy dist = %.2f\n", nearest);
		last_debug = time(NULL);
	}
}

/**
 * Desenha texto centralizado
 */
static void	draw_centered_text(t_game *g, char *text, int y, int color)
{
	int		text_len;
	int		x;
	
	text_len = ft_strlen(text);
	x = (WIN_W - (text_len * 10)) / 2;  // Aproximação (10 pixels por char)
	
	mlx_string_put(g->mlx, g->win, x, y, color, text);
}

/**
 * Desenha a tela de Game Over
 */
void	draw_game_over(t_game *g)
{
	int		x;
	int		y;

	if (!g->enemy_sys.game_over)
		return;

	// Preenche tela de preto
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel_to_img(&g->screen, x, y, 0x000000);
			x++;
		}
		y++;
	}

	// Desenha na imagem primeiro
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);

	// Depois desenha o texto por cima (usando mlx_string_put)
	draw_centered_text(g, "GAME OVER", WIN_H / 2 - 50, 0xFF0000);
	draw_centered_text(g, "Press ESC to exit", WIN_H / 2 + 20, 0xFFFFFF);
}

/**
 * Desenha contador de inimigos no HUD
 */
void	draw_enemy_counter(t_game *g)
{
	char	text[50];
	int		active_count;
	int		i;

	if (g->enemy_sys.game_over)
		return;

	// Conta inimigos ativos
	active_count = 0;
	i = 0;
	while (i < g->enemy_sys.enemy_count)
	{
		if (g->enemy_sys.enemies[i].active)
			active_count++;
		i++;
	}

	snprintf(text, sizeof(text), "Enemies: %d", active_count);
	mlx_string_put(g->mlx, g->win, 10, WIN_H - 20, 0xFFFFFF, text);
}