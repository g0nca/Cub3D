/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:04:49 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/17 09:47:10 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void draw_player(t_game *g)
{
    int px;
    int py;
    int r;
    int i;
    int j;

    // O jogador está sempre no centro do minimapa circular
    px = MINIMAP_X;
    py = MINIMAP_Y;
    r = 4;  // Raio do ponto do jogador

    // Desenha o círculo do jogador
    j = -r;
    while (j <= r)
    {
        i = -r;
        while (i <= r)
        {
            if (i * i + j * j <= r * r)
                put_pixel_to_img(&g->screen, px + i, py + j, 0x008000);
            i++;
        }
        j++;
    }

    // Desenha linha de direção
    int line_len = 15;
    int k = 0;
    while (k < line_len)
    {
        int lx = px + (int)(cos(g->player.angle) * k);
        int ly = py + (int)(sin(g->player.angle) * k);
    put_pixel_to_img(&g->screen, lx, ly, 0xFFFF00);
        k++;
    }
}
