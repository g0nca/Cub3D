/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:04:49 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/05 09:32:44 by joaomart         ###   ########.fr       */
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
                put_pixel_to_img(&g->screen, px + i, py + j, 0xFF0000);
            i++;
        }
        j++;
    }

    // Desenha linha de direção
    for (int k = 0; k < 10; k++)
    {
        int lx = px + (int)(cos(g->player.angle) * k);
        int ly = py + (int)(sin(g->player.angle) * k);
        put_pixel_to_img(&g->screen, lx, ly, 0xFFFF00);
    }
}
