/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_gui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:25:05 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:29:57 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	draw_centered_text(t_game *g, char *text, int y, int color)
{
	int		text_len;
	int		x;

	text_len = ft_strlen(text);
	x = (WIN_W - (text_len * 10)) / 2;
	mlx_string_put(g->mlx, g->win, x, y, color, text);
}

void	draw_game_over(t_game *g)
{
	int		x;
	int		y;

	if (!g->enemy_sys.game_over)
		return ;
	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			put_pixel_to_img(&g->screen, x, y, 0x000000);
	}
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);
	draw_centered_text(g, "GAME OVER", WIN_H / 2 - 50, 0xFF0000);
	draw_centered_text(g, "Press ESC to exit", WIN_H / 2 + 20, 0xFFFFFF);
}

void	draw_game_win(t_game *g)
{
	int		x;
	int		y;

	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
			put_pixel_to_img(&g->screen, x, y, 0x000000);
	}
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);
	draw_centered_text(g, "Winner !!!!", WIN_H / 2 - 50, 0x00FF00);
	draw_centered_text(g, "Press ESC to exit", WIN_H / 2 + 20, 0xFFFFFF);
}

void	draw_enemy_counter(t_game *g)
{
	char	text[50];
	int		active_count;
	int		i;

	if (g->enemy_sys.game_over)
		return ;
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
