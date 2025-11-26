/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:20:28 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/26 14:30:54 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	copy_to_struct(char **av, t_map *map);

t_map	*read_file_parse(char **av, t_cub *cub)
{
	t_map	*map;
	int		line_count;

	map = init_map_struct();
	map->cub_struct = cub;
	line_count = ft_line_count(av, map);
	if (line_count <= 0)
	{
		free(map);
		return (NULL);
	}
	map->grid = malloc(sizeof(char *) * (line_count + 1));
	if (!map->grid)
	{
		free(map);
		return (NULL);
	}
	if (copy_to_struct(av, map) == -1)
		return (NULL);
	separate_map_info(map);
	trim_newline_center(map, 1);
	if (check_map_closed(map) == 1)
		map->exit_flag = 1;
	return (map);
}

t_map	*separate_map_info(t_map *map)
{
	int	i;
	int	info_status;

	i = 0;
	while (map->grid[i])
	{
		if (map->grid[i][0] == '\n')
			i++;
		info_status = 0;
		info_status = check_info(map->grid[i]);
		if (info_status >= 1 && info_status <= 6)
			save_info_to_map_struct(map, map->grid[i], info_status);
		if (info_status == 0)
		{
			if (map->grid[i] == NULL)
				break ;
			check_map(map, &i);
		}
		i++;
	}
	check_if_all_elements_exists(map);
	map = save_only_map_lines(map);
	trim_newline_center(map, 0);
	return (map);
}

static int	copy_to_struct(char **av, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	fd = return_fd(av, map);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (-1);
	}
	i = 0;
	while (line != NULL)
	{
		map->grid[i] = line;
		if ((int)ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		line = get_next_line(fd);
		i++;
	}
	map->grid[i] = NULL;
	close(fd);
	return (0);
}

void	check_if_all_elements_exists(t_map *map)
{
	if (!map->no_texture)
		print_error_and_exit_free("Missing North Path for texture", 1, map);
	if (!map->so_texture)
		print_error_and_exit_free("Missing South Path for texture", 1, map);
	if (!map->we_texture)
		print_error_and_exit_free("Missing West Path for texture", 1, map);
	if (!map->ea_texture)
		print_error_and_exit_free("Missing East Path for texture", 1, map);
	if (!map->floor_color)
		print_error_and_exit_free("Missing Floor Color", 1, map);
	if (!map->ceiling_color)
		print_error_and_exit_free("Missing Ceiling Color", 1, map);
}

int	check_map_closed(t_map *map)
{
	char	**map_copy;
	int		start_x;
	int		start_y;
	int		result;

	map->height = map_height(map);
	map_copy = copy_map_grid(map);
	if (!map_copy)
	{
		ft_free_map(map_copy);
		print_error_and_exit_free("No space left on device", 1, map);
	}
	if (!find_player_position_parse(map, &start_x, &start_y))
	{
		ft_free_map(map_copy);
		print_error_and_exit_free("No player position founded", 1, map);
	}
	result = flood_fill(map, map_copy, start_x, start_y);
	ft_free_map(map_copy);
	if (!result)
		print_error_and_exit_free("Map is not closed by walls", 1, map);
	return (0);
}
