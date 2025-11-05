/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:48 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/05 09:50:52 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        print_error_and_exit("mlx_init failed");
    game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "Cub3D");
    if (!game->win)
        print_error_and_exit("mlx_new_window failed");

    // Cria buffer de imagem para evitar flickering
    game->screen.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
    if (!game->screen.img)
        print_error_and_exit("mlx_new_image failed");
    game->screen.addr = mlx_get_data_addr(game->screen.img,
        &game->screen.bpp, &game->screen.line_len, &game->screen.endian);

    init_images(game);
    game->player.x = 0.0;
    game->player.y = 0.0;
    game->player.angle = 0.0;
    game->player.move_speed = 0.01;
    game->player.rot_speed = 0.01;

    // Inicializa array de teclas
    int i = 0;
    while (i < 256)
    {
        game->keys[i] = 0;
        i++;
    }
    game->key_left = 0;
    game->key_right = 0;
}
