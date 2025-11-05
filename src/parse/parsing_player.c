/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 09:33:25 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/05 09:33:28 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static double get_angle_from_direction(char dir)
{
    if (dir == 'N')
        return (3 * M_PI / 2);  // 270 graus - Norte (cima)
    else if (dir == 'S')
        return (M_PI / 2);      // 90 graus - Sul (baixo)
    else if (dir == 'E')
        return (0);             // 0 graus - Este (direita)
    else if (dir == 'W')
        return (M_PI);          // 180 graus - Oeste (esquerda)
    return (0);
}

int find_player_position(t_game *game)
{
    int x;
    int y;
    char c;

    y = 0;
    while (game->map.grid[y])
    {
        x = 0;
        while (game->map.grid[y][x])
        {
            c = game->map.grid[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                game->player.x = x + 0.5;
                game->player.y = y + 0.5;
                game->player.angle = get_angle_from_direction(c);
                game->map.grid[y][x] = '0';  // Substitui por chão
                return (1);
            }
            x++;
        }
        y++;
    }
    return (0);  // Player não encontrado
}
