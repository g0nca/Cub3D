/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:04:49 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/04 15:08:55 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    draw_player(t_game *g)
{
    int px;
    int py;
    int r;
    int i;
    int j;
    int offset_x = 10;
    int offset_y = 10;

    px = offset_x + (int)(g->player.x * TILE_SIZE);
    py = offset_y + (int)(g->player.y * TILE_SIZE);
    r = 3;

    j = -r;
    while (j <= r)
    {
        i = -r;
        while (i <= r)
        {
            if (i * i + j * j <= r * r)
                mlx_pixel_put(g->mlx, g->win, px + i, py + j, 0xFF0000);
            i++;
        }
        j++;
    }

    // Desenha linha de direção
    /* int dir_x = px + (int)(cos(g->player.angle) * 10);
    int dir_y = py + (int)(sin(g->player.angle) * 10); */
    for (int k = 0; k < 10; k++)
    {
        int lx = px + (int)(cos(g->player.angle) * k);
        int ly = py + (int)(sin(g->player.angle) * k);
        mlx_pixel_put(g->mlx, g->win, lx, ly, 0xFFFF00);  // Linha amarela
    }
}
