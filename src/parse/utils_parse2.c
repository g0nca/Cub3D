/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:53:56 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/24 15:36:18 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_texture(int type)
{
	if (type == NO)
		printf("North Texture --> ");
	else if (type == SO)
		printf("South Texture --> ");
	else if (type == WE)
		printf("West Texture --> ");
	else if (type == EA)
		printf("East Texture --> ");
}

int	return_fd(char **av, t_map *map)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		free(map->grid);
		free(map);
		return (-1);
	}
	return (fd);
}
