/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:16 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/04 15:11:27 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int ac, char **av)
{
    t_game game;

    parsing_input(ac, av);

    //temporario
    game.map.grid = malloc(sizeof(char *) * 6);
    game.map.grid[0] = ft_strdup("11111");
    game.map.grid[1] = ft_strdup("10001");
    game.map.grid[2] = ft_strdup("10N01");
    game.map.grid[3] = ft_strdup("10001");
    game.map.grid[4] = ft_strdup("11111");
    game.map.grid[5] = NULL;

    init_game(&game);

    game.player.x = 2.5;
    game.player.y = 2.5;
    game.player.angle = 3 * M_PI / 2;

    // Renderiza tudo uma vez
    render_3d_view(&game);
    draw_minimap(&game);
    draw_player(&game);

    mlx_hook(game.win, 17, 0, close_window, &game);
    mlx_key_hook(game.win, handle_keys, &game);
    mlx_loop(game.mlx);
    return (0);
}
