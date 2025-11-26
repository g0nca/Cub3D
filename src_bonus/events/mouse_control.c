/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:00:00 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:26 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/**
 * Handler para movimento do mouse
 * x, y: coordenadas atuais do mouse na janela
 */
int	mouse_move(int x, int y, t_game *g)
{
	int		dx;
	double	rotation;

	(void)y;
	if (g->enemy_sys.game_over)
		return (0);
	if (g->win_game == g->enemy_sys.enemy_count)
		return (0);
	dx = x - (WIN_W / 2);
	if (dx > -5 && dx < 5)
		return (0);
	rotation = dx * MOUSE_SENS;
	g->player.angle += rotation;
	if (g->player.angle < 0)
		g->player.angle += 2 * M_PI;
	if (g->player.angle >= 2 * M_PI)
		g->player.angle -= 2 * M_PI;
	mlx_mouse_move(g->mlx, g->win, WIN_W / 2, WIN_H / 2);
	if (g->enemy_sys.game_over)
	{
		draw_game_over(g);
		return (0);
	}
	handle_render(g);
	return (0);
}

/**
 * Esconde o cursor do mouse (para experiência mais imersiva)
 */
void	hide_mouse_cursor(t_game *g)
{
	mlx_mouse_hide(g->mlx, g->win);
}

/**
 * Mostra o cursor do mouse
 */
void	show_mouse_cursor(t_game *g)
{
	mlx_mouse_show(g->mlx, g->win);
}
