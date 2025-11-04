/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:33 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/04 15:06:57 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void draw_square(t_game *g, int x, int y, int color)
{
    int i;
    int j;
    int offset_x = 10;  // Margem da esquerda
    int offset_y = 10;  // Margem de cima

    j = 0;
    while (j < TILE_SIZE)
    {
        i = 0;
        while (i < TILE_SIZE)
        {
            mlx_pixel_put(g->mlx, g->win,
                offset_x + x * TILE_SIZE + i,
                offset_y + y * TILE_SIZE + j, color);
            i++;
        }
        j++;
    }
}

void    draw_minimap(t_game *g)
{
    int x;
    int y;
    char c;

    if (!g->map.grid)
        return;

    y = 0;
    while (g->map.grid[y])
    {
        x = 0;
        while (g->map.grid[y][x])
        {
            c = g->map.grid[y][x];
            if (c == '1')
                draw_square(g, x, y, 0x333333);  // Paredes escuras
            else
                draw_square(g, x, y, 0xCCCCCC);  // Chão claro
            x++;
        }
        y++;
    }
}

