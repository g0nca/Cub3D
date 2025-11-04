/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:48 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/04 14:58:10 by joaomart         ###   ########.fr       */
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
    init_images(game);
	game->player.x = 0.0;
    game->player.y = 0.0;
    game->player.angle = 0.0;
    game->player.move_speed = 0.1;
    game->player.rot_speed = 0.05;
}


