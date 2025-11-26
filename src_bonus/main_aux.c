/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:34:23 by joaomart          #+#    #+#             */
/*   Updated: 2025/11/26 15:42:40 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	init_cub_struct(t_cub **cub, char **av)
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

void	setup_game_data(t_game *game, t_cub *cub)
{
	game->map = *(cub->map);
	game->cub = *cub;
	free(cub);
}

void	init_player_if_needed(t_game *game)
{
	if (!find_player_position(game))
	{
		game->player.x = 2.5;
		game->player.y = 2.5;
		game->player.angle = 3 * M_PI / 2;
	}
}

void	init_game_render(t_game *game)
{
	init_enemy_system(game);
	render_weapon(game);
	render_3d_view(game);
	draw_minimap(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	draw_enemy_counter(game);
	print_map_struct(&game->cub, NULL);
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	if (game->win_game != game->enemy_sys.enemy_count)
		mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_move(game->mlx, game->win, WIN_W / 2, WIN_H / 2);
	mlx_loop_hook(game->mlx, handle_keys, game);
}
