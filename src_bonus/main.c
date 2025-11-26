/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:16 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 15:42:04 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
	if (init_cub_struct(&cub, av))
		return (1);
	setup_game_data(&game, cub);
	init_game(&game);
	init_player_if_needed(&game);
	init_game_render(&game);
	init_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
