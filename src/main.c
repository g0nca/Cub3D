/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:16 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 15:31:45 by joaomart         ###   ########.fr       */
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

static int	init_cub(t_cub **cub, char **av)
{
	*cub = malloc(sizeof(t_cub));
	if (!*cub)
		return (1);
	(*cub)->map = read_file_parse(av, *cub);
	if ((*cub)->map->exit_flag == 1 || !check_elements((*cub)->map))
	{
		print_error_and_exit_without_free("Loading Elements", 0, (*cub)->map);
		ft_free_all(*cub);
		free(*cub);
		return (1);
	}
	return (0);
}

static void	setup_game(t_game *game, t_cub *cub)
{
	game->map = *(cub->map);
	game->cub = *cub;
	free(cub);
}

static void	init_player_if_missing(t_game *game)
{
	if (!find_player_position(game))
	{
		game->player.x = 2.5;
		game->player.y = 2.5;
		game->player.angle = 3 * M_PI / 2;
	}
}

int	main(int ac, char **av)
{
	t_cub	*cub;
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	parsing_input(ac, av);
	if (init_cub(&cub, av))
		return (1);
	setup_game(&game, cub);
	init_game(&game);
	init_player_if_missing(&game);
	render_3d_view(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.screen.img, 0, 0);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_mouse_move(game.mlx, game.win, WIN_W / 2, WIN_H / 2);
	mlx_loop_hook(game.mlx, handle_keys, &game);
	print_map_struct(&game.cub, NULL);
	mlx_loop(game.mlx);
	return (0);
}
