/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:31:35 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	print_error_and_exit_without_free(const char *message,
	int exit_flag, t_map *map)
{
	(void)map;
	printf("Error : %s\n", message);
	if (exit_flag == 1)
	{
		exit(EXIT_FAILURE);
	}
}

void	print_error_and_exit_free(const char *message,
	int exit_flag, t_map *map)
{
	printf("Error : %s\n", message);
	if (exit_flag == 1)
	{
		map->exit_flag = 1;
		ft_free_map(map->grid);
		free(map->cub_struct);
		free(map->no_texture);
		free(map->so_texture);
		free(map->we_texture);
		free(map->ea_texture);
		free(map->floor_color);
		free(map->ceiling_color);
		free(map);
		exit(EXIT_FAILURE);
	}
}
