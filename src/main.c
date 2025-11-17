/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrade <andrade@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:16 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/17 12:10:37 by andrade          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void print_map_struct(t_cub *cub, t_map *map)
{
    int i = 0;
    if (cub != NULL)
    {
        while (cub->map->grid[i])
        {
            printf("%s\n", cub->map->grid[i]);
            i++;
        }
    }
    else if (map != NULL)
    {
        while (map->grid[i])
        {
            printf("%s\n", map->grid[i]);
            i++;
        }
    }
}
int main(int ac, char **av)
{
    t_cub   *cub;
    t_game game;

    /* Initialize game struct to all zeros to avoid garbage in enemy_sys */
    ft_bzero(&game, sizeof(t_game));
    
    cub = malloc(sizeof(t_cub));
    if (!cub)
        return (1);
    parsing_input(ac, av);
    cub->map = read_file_parse(av, cub);
    if (cub->map->exit_flag == 1 || check_elements(cub->map) == false)
    {
        print_error_and_exit_without_free("Loading Elements", 0, cub->map);
        ft_free_all(cub);
        free(cub);
        return (1);
    }
    game.map = *(cub->map);
    game.cub = *(cub);
    free(cub);
    cub = NULL;
    init_game(&game);
    if (!find_player_position(&game))
    {
        game.player.x = 2.5;
        game.player.y = 2.5;
        game.player.angle = 3 * M_PI / 2;
    }
    //Inicializa sistema de inimigos
    init_enemy_system(&game);
    printf("[DEBUG] init_enemy_system done\n");
    // Renderização inicial
    render_3d_view(&game);
    printf("[DEBUG] render_3d_view done\n");
    render_enemies(&game);  // <-- ADICIONAR ESTA LINHA
    printf("[DEBUG] render_enemies done\n");
    draw_minimap(&game);
    printf("[DEBUG] draw_minimap done\n");
    draw_player(&game);
    printf("[DEBUG] draw_player done\n");
    mlx_put_image_to_window(game.mlx, game.win, game.screen.img, 0, 0);
    printf("[DEBUG] mlx_put_image_to_window done\n");
    draw_enemy_counter(&game);  // <-- ADICIONAR ESTA LINHA
    printf("[DEBUG] draw_enemy_counter done\n");

    // Registra eventos de teclado
    mlx_hook(game.win, 2, 1L<<0, key_press, &game);      // Key press
    mlx_hook(game.win, 3, 1L<<1, key_release, &game);    // Key release
    mlx_hook(game.win, 17, 0, close_window, &game);      // Window close

    // Registra eventos de mouse
    mlx_hook(game.win, 6, 1L<<6, mouse_move, &game);     // Mouse move

    // Esconde o cursor para experiência mais imersiva
    hide_mouse_cursor(&game);

    // Centra o cursor no meio da janela
    mlx_mouse_move(game.mlx, game.win, WIN_W / 2, WIN_H / 2);

    mlx_loop_hook(game.mlx, handle_keys, &game);         // Loop contínuo
    print_map_struct(&game.cub, NULL);
    mlx_loop(game.mlx);
    return (0);
}

