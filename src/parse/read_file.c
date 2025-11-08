/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:20:28 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/08 20:57:42 by marvin           ###   ########.fr       */
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
	line_count = 0;
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

t_map	*read_file_parse(char **av)
{
	t_map	*map;
	int		line_count;
	

	map = init_map_struct();
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
t_map	*save_info_to_map_struct(t_map *map, char *line, int info_status)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (info_status == NO)
		map->no_texture = ft_strdup(&line[i]);
	else if (info_status == SO)
		map->so_texture = ft_strdup(&line[i]);
	else if (info_status == WE)
		map->we_texture = ft_strdup(&line[i]);
	else if (info_status == EA)
		map->ea_texture = ft_strdup(&line[i]);
	else if (info_status == F)
		map->floor_color = ft_strdup(&line[i]);
	else if (info_status == C)
		map->ceiling_color = ft_strdup(&line[i]);
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
			{
				print_error_and_exit_without_free("Error : Invalid Map", 0, map);
				return (-1);
			}
			map->last_map_line = *i;
		}
		map->end = *i;
	}
	else if (map->start != 0)
	{
		print_error_and_exit_without_free("Error : Invalid Map", 0, map);
		return (-1);
	}
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
	return (map);
}
