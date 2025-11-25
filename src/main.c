/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:16 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/25 13:14:46 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map_struct(t_cub *cub, t_map *map)
{
	int		i;

	i = 0;
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

int	main(int ac, char **av)
{
	t_cub	*cub;
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	parsing_input(ac, av);
	cub = malloc(sizeof(t_cub));
	if (!cub)
		return (1);
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
	init_enemy_system(&game);
	render_weapon(&game);
	render_3d_view(&game);
	render_enemies(&game);
	draw_minimap(&game);
	draw_player(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.screen.img, 0, 0);
	draw_enemy_counter(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	if (game.win_game != game.enemy_sys.enemy_count)
		mlx_hook(game.win, 6, 1L << 6, mouse_move, &game);
	mlx_mouse_move(game.mlx, game.win, WIN_W / 2, WIN_H / 2);
	mlx_loop_hook(game.mlx, handle_keys, &game);
	print_map_struct(&game.cub, NULL);
	mlx_loop(game.mlx);
	return (0);
}
//hide_mouse_cursor(&game);

