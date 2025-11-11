/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:20:28 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/10 16:30:44 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_map	*init_map_struct(void)
{
	t_map *map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = NULL;
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
	map->exit_flag = 0;
	map->start = 0;
	map->last_map_line = 0;
	map->end = 0;
	map->height = 0;
	map->width = 0;
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
		free(map->map);
		free(map);
		return (-1);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->map[i] = line;
		if ((int)ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
		i++;
	}
	map->map[i] = NULL;
	map->height = i;
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
	map->map = malloc(sizeof(char *) * (line_count + 1));
	if (!map->map)
	{
		free(map);
		return (NULL);
	}
	if (copy_to_struct(av, map) == -1)
		return (NULL);
	separate_map_info(map);
	return (map);
}
int		check_info(char *line)
{
	int i;

	i = 0;
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

int		is_map_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W' || line[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int		check_map(t_map *map, int *i)
{
	if (is_map_line(map->map[*i]))
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
		only_map[j] = ft_strdup(map->map[i]);
		if (ft_strlen(only_map[j]) - 1 == '\n')
			only_map[j][ft_strlen(only_map[j]) - 1] = '\0';
		j++;
		i++;
	}
	only_map[j] = NULL;
	i = 0;
	ft_free_map(map->map);
	map->map = only_map;
	return (map);
}
t_map	*separate_map_info(t_map *map)
{
	int i;
	int	info_status;

	i = 0;
	while (map->map[i])
	{
		info_status = 0;
		info_status = check_info(map->map[i]);
		if (info_status >= 1 && info_status <= 6)
			save_info_to_map_struct(map, map->map[i], info_status);
		if (info_status == 0)
		{
			if (check_map(map, &i) == -1)
				return (map);
		}
		i++;
	}
	map = save_only_map_lines(map);
	trim_newline(map->no_texture);
	trim_newline(map->so_texture);
	trim_newline(map->we_texture);
	trim_newline(map->ea_texture);
	trim_newline(map->floor_color);
	trim_newline(map->ceiling_color);
	return (map);
}
