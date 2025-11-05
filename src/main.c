/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:16 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/05 09:52:45 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int ac, char **av)
{
    t_game game;

    parsing_input(ac, av);

    // Temporário - criar mapa de teste
    game.map.grid = malloc(sizeof(char *) * 6);
    game.map.grid[0] = ft_strdup("11111");
    game.map.grid[1] = ft_strdup("10001");
    game.map.grid[2] = ft_strdup("10101");  // N = Norte
    game.map.grid[3] = ft_strdup("10N01");
    game.map.grid[4] = ft_strdup("11111");
    game.map.grid[5] = NULL;

    init_game(&game);

    // Encontra posição e orientação do player no mapa
    if (!find_player_position(&game))
    {
        // Fallback se não encontrar
        game.player.x = 2.5;
        game.player.y = 2.5;
        game.player.angle = 3 * M_PI / 2;
    }

    // Renderiza primeira frame
    render_3d_view(&game);
    draw_minimap(&game);
    draw_player(&game);
    mlx_put_image_to_window(game.mlx, game.win, game.screen.img, 0, 0);

    // Hooks para movimento contínuo
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);      // Key press
    mlx_hook(game.win, 3, 1L<<1, key_release, &game);    // Key release
    mlx_hook(game.win, 17, 0, close_window, &game);      // Window close
    mlx_loop_hook(game.mlx, handle_keys, &game);         // Loop contínuo

    mlx_loop(game.mlx);
    return (0);
}
