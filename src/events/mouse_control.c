/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:00:00 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/12 15:00:21 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * Handler para movimento do mouse
 * x, y: coordenadas atuais do mouse na janela
 */
int	mouse_move(int x, int y, t_game *g)
{
	int		dx;
	double	rotation;

	(void)y;  // Não usamos movimento vertical

	// Calcula diferença em relação ao centro da janela
	dx = x - (WIN_W / 2);

	// Se o mouse estiver muito próximo do centro, não faz nada
	if (dx > -5 && dx < 5)
		return (0);

	// Calcula rotação baseada no movimento horizontal
	rotation = dx * MOUSE_SENSITIVITY;

	// Aplica rotação ao jogador
	g->player.angle += rotation;

	// Normaliza ângulo entre 0 e 2*PI
	if (g->player.angle < 0)
		g->player.angle += 2 * M_PI;
	if (g->player.angle >= 2 * M_PI)
		g->player.angle -= 2 * M_PI;

	// Recentra o cursor no meio da janela
	mlx_mouse_move(g->mlx, g->win, WIN_W / 2, WIN_H / 2);

	// Re-renderiza a cena
	render_3d_view(g);
	draw_minimap(g);
	draw_player(g);
	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);

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
