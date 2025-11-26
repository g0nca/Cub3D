/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:04:49 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/26 14:31:20 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

/* Desenha o ponto central (corpo do jogador) */
static void	draw_player_dot(t_game *g)
{
	int	i;
	int	j;
	int	r;

	r = 4;
	j = -r;
	while (j <= r)
	{
		i = -r;
		while (i <= r)
		{
			if (i * i + j * j <= r * r)
				put_pixel_to_img(&g->screen, MINIMAP_X + i,
					MINIMAP_Y + j, 0x008000);
			i++;
		}
		j++;
	}
}

/* Desenha a linha amarela indicando a direção */
static void	draw_direction_line(t_game *g)
{
	int	k;
	int	len;
	int	lx;
	int	ly;

	len = 15;
	k = 0;
	while (k < len)
	{
		lx = MINIMAP_X + (int)(cos(g->player.angle) * k);
		ly = MINIMAP_Y + (int)(sin(g->player.angle) * k);
		put_pixel_to_img(&g->screen, lx, ly, 0xFFFF00);
		k++;
	}
}

/* Função principal */
void	draw_player(t_game *g)
{
	draw_player_dot(g);
	draw_direction_line(g);
}
