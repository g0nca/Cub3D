/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:20:28 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/12 14:51:59 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_map	*init_map_struct(void)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->grid = NULL;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color = NULL;
	map->ceiling_color = NULL;
	map->floor_rgb[0] = -1;
	map->floor_rgb[1] = -1;
	map->floor_rgb[2] = -1;
	map->ceiling_rgb[0] = -1;
	map->ceiling_rgb[1] = -1;
	map->ceiling_rgb[2] = -1;
	map->start_x = -1;
	map->start_y = -1;
	map->exit_flag = 0;
	map->start = 0;
	map->last_map_line = 0;
	map->end = 0;
	map->height = 0;
	map->width = 0;
	map->player_p = false;
	return (map);
}

static int		ft_line_count(char **av, t_map *map)
{
	int		line_count;
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (-1);
	}
	line_count = 1;
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		print_error_and_exit_FREE("Empty File", 1, map);
	}
	free(line);
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}

static int	copy_to_struct(char **av, t_map *map)
{
	int fd;
	int i;
	char *line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		free(map->grid);
		free(map);
		return (-1);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->grid[i] = line;
		if ((int)ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		i++;
	}
	map->grid[i] = NULL;
	close(fd);	
	return (0);
}

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
int		check_info(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == 'N' && line[i + 1] == 'O')
			return (NO);
		else if (line[i] == 'S' && line[i + 1] == 'O')
			return (SO);
		else if (line[i] == 'W' && line[i + 1] == 'E')
			return (WE);
		else if (line[i] == 'E' && line[i + 1] == 'A')
			return (EA);
		else if (line[i] == 'F')
			return (F);
		else if (line[i] == 'C')
			return (C);
		i++;
	}
	return (0);
}

void	trim_newline(char *str)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			return ;
		}
		i++;
	}
}

void	save_texture_or_color2(t_map *map, char *value, int info_status)
{

	if (info_status == WE)
	{
		if (map->we_texture == NULL)
			map->we_texture = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
	else if (info_status == EA)
	{
		if (map->ea_texture == NULL)
			map->ea_texture = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
	else if (info_status == F)
	{
		if (map->floor_color == NULL)
			map->floor_color = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
	else if (info_status == C)
	{
		if (map->ceiling_color == NULL)
			map->ceiling_color = ft_strdup(value);
		else
			map->exit_flag = 1;
	}
}

t_map	*save_info_to_map_struct(t_map *map, char *line, int info_status)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (info_status == NO)
	{
		if (map->no_texture == NULL)
			map->no_texture = ft_strdup(&line[i]);
		else
			map->exit_flag = 1;
	}
	else if (info_status == SO)
	{
		if (map->so_texture == NULL)
			map->so_texture = ft_strdup(&line[i]);
		else
			map->exit_flag = 1;
	}
	save_texture_or_color2(map, &line[i], info_status);
	return (map);
}

int		is_map_line(char *line, t_map *map)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (map->player_p == false && (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E'))
			map->player_p = true;
		else if (map->player_p == true && (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E'))
			print_error_and_exit_FREE("Only SinglePlayer Game, NOT MULTIPLAYER", 1, map);
 		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int		check_map(t_map *map, int *i)
{
	if (is_map_line(map->grid[*i], map))
	{
		if (map->start == 0)
		{
			map->start = *i;
			map->last_map_line = *i;
		}
		else
		{
			if (*i != map->last_map_line + 1)
				print_error_and_exit_FREE("Invalid Map", 1, map);
			map->last_map_line = *i;
		}
		map->end = *i;
	}
	else if (map->start != 0)
		print_error_and_exit_FREE("Invalid Map", 1, map);
	return (0);
}

t_map	*save_only_map_lines(t_map *map)
{
	int		i;
	int		j;
	char	**only_map;
	
	if (map->start == 0 && map->end == 0)
		return (map);
	only_map = malloc(sizeof(char *) * (map->end - map->start + 2));
	if (!only_map)
		return (NULL);
	i = map->start;
	j = 0;
	while (i <= map->end)
	{
		only_map[j] = ft_strdup(map->grid[i]);
		if (ft_strlen(only_map[j]) - 1 == '\n')
			only_map[j][ft_strlen(only_map[j]) - 1] = '\0';
		j++;
		i++;
	}
	only_map[j] = NULL;
	i = 0;
	ft_free_map(map->grid);
	map->grid = only_map;
	return (map);
}
void	check_if_all_elements_exists(t_map *map)
{
	if (!map->no_texture)
		print_error_and_exit_FREE("Missing North Path for texture", 1, map);
	if (!map->so_texture)
		print_error_and_exit_FREE("Missing South Path for texture", 1, map);
	if (!map->we_texture)
		print_error_and_exit_FREE("Missing West Path for texture", 1, map);
	if (!map->ea_texture)
		print_error_and_exit_FREE("Missing East Path for texture", 1, map);
	if (!map->floor_color)
		print_error_and_exit_FREE("Missing Floor Color", 1, map);
	if (!map->ceiling_color)
		print_error_and_exit_FREE("Missing Ceiling Color", 1, map);

}

void	trim_newline_center(t_map *map, int flag)
{
	int i;

	i = 0;
	if (flag == 0)
	{
		trim_newline(map->no_texture);
		trim_newline(map->so_texture);
		trim_newline(map->we_texture);
		trim_newline(map->ea_texture);
		trim_newline(map->floor_color);
		trim_newline(map->ceiling_color);
	}
	else if (flag == 1)
	{
		while (map->grid[i])
		{
			trim_newline(map->grid[i]);
			i++;
		}
	}
}
t_map	*separate_map_info(t_map *map)
{
	int i;
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
			if (check_map(map, &i) == -1)
				return (map);
		}
		i++;
	}
	check_if_all_elements_exists(map);
	map = save_only_map_lines(map);
	trim_newline_center(map, 0);
	return (map);
}
int		map_height(t_map *map)
{
	int i;

	i = 0;
	while (map->grid[i])
		i++;
	return (i);
}

char	**copy_map_grid(t_map *map)
{
	char	**map_copy;
	int		i;

	if (!map->grid)
		return (NULL);
	map_copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (map->grid[i])
	{
		map_copy[i] = ft_strdup(map->grid[i]);
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}
int		find_player_position_parse(t_map *map, int *start_x, int *start_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'N' || map->grid[y][x] == 'S' || map->grid[y][x] == 'W' || map->grid[y][x] == 'E')
			{
				*start_x = x;
				*start_y = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
int		flood_fill(char **map_copy, int x, int y, int width, int height)
{
	char	c;
	int		line_len;

	if (y < 0 || y >= height || x < 0 || x >= width)
		return (0);
	line_len = ft_strlen(map_copy[y]);
	if (x < 0 || x >= line_len)
		return (0);
	c = map_copy[y][x];
	if (c == '1' || c == 'V')
		return (1);
	if (c == ' ' || c == '\0' || c == '\n')
	{
		if ((c == ' ' || c == '\0') && (y == 0 || y == height -1 || x == 0 || x == width -1))
			return (0);
	}
	map_copy[y][x] = 'V';
	if (!flood_fill(map_copy, x, y - 1, width, height))
		return (0);
	if (!flood_fill(map_copy, x, y + 1, width, height))
		return (0);
	if (!flood_fill(map_copy, x - 1, y, width, height))
		return (0);
	if (!flood_fill(map_copy, x + 1, y, width, height))
		return (0);
	return (1);
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
		print_error_and_exit_FREE("No space left on device", 1, map);
	}
	if (!find_player_position_parse(map, &start_x, &start_y))
	{
		ft_free_map(map_copy);
		print_error_and_exit_FREE("No player position founded", 1, map);
	}
	result = flood_fill(map_copy, start_x, start_y, map->width, map->height);	
	ft_free_map(map_copy);
	if (!result)
	{
		print_error_and_exit_FREE("Map is not closed by walls\nMap are closing by system", 0, map);
		return (1);
	}
	return (0);
}

