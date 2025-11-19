/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:48 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/19 15:20:26 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void init_weapon_assets(t_game *game)
{
    int i;

    char *paths[WEAPON_FRAMES] = {
        "assets/gun_textures/gun0.xpm", // Muda para os teus caminhos reais
        "assets/gun_textures/gun1.xpm",
        "assets/gun_textures/gun2.xpm",
        "assets/gun_textures/gun3.xpm",
        "assets/gun_textures/gun4.xpm"
    };
    i = 0;

    while (i < WEAPON_FRAMES)
    {
        game->weapon.textures[i].img = mlx_xpm_file_to_image(game->mlx, paths[i], 
                                                &game->weapon.textures[i].width, 
                                                &game->weapon.textures[i].height);
        if (!game->weapon.textures[i].img)
        {
            print_error_and_exit_without_free("Failed loading weapon textures", 0, game->cub.map);
            close_window(game);
        }
        game->weapon.textures[i].addr = mlx_get_data_addr(game->weapon.textures[i].img, 
                                            &game->weapon.textures[i].bpp, 
                                            &game->weapon.textures[i].line_len, 
                                            &game->weapon.textures[i].endian);
        i++;
    }
    game->weapon.is_firing = 0;
    game->weapon.current_frame = 0;
}
static void     init_keys(t_game *game)
{
    int i;

    i = 0;
    while (i < 256)
    {
        game->keys[i] = 0;
        i++;
    }
}
void    init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        print_error_and_exit_FREE("mlx_init failed", 1, NULL);
    game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "Cub3D");
    if (!game->win)
        print_error_and_exit_FREE("mlx_init failed", 1, NULL);
    game->screen.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
    if (!game->screen.img)
        print_error_and_exit_FREE("mlx_init failed", 1, NULL);
    game->screen.addr = mlx_get_data_addr(game->screen.img,
        &game->screen.bpp, &game->screen.line_len, &game->screen.endian);
    init_images(game);
    init_weapon_assets(game);
    game->win_game = 0;
    game->player.x = 0.0;
    game->player.y = 0.0;
    game->player.angle = 0.0;
    game->player.move_speed = 0.02;
    game->player.rot_speed = 0.01;
    init_keys(game);
    game->key_left = 0;
    game->key_right = 0;
}
