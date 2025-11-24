/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elem_map2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:40:44 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/24 12:10:36 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void safe_exit_with_splits(char *msg, t_map *map, 
                                   char **floor_split, char **ceiling_split)
{
    free_split_array(floor_split);
    free_split_array(ceiling_split);
    print_error_and_exit_FREE(msg, 1, map);
}

void save_color_values(char *color_str, t_map *map, int floor_or_ceiling, 
                               int index, char **floor_split, char **ceiling_split)
{
    int value;
    
    value = ft_atoi(color_str);
    if (value < 0 || value > 255)
        safe_exit_with_splits("The numbers exceed the valid range", 
                              map, floor_split, ceiling_split);
    if (floor_or_ceiling == 1)
        map->floor_rgb[index] = value;
    else if (floor_or_ceiling == 0)
        map->ceiling_rgb[index] = value;
}

/* Valida o formato de uma string individual (verifica pontos e digitos) */
static void	check_color_format(char *s, t_map *map, char **f_sp, char **c_sp)
{
	int		j;
	bool	num_exist;

	j = 0;
	num_exist = false;
	while (s[j])
	{
		if (s[j] == '.')
			safe_exit_with_splits("Invalid decimal numbers", map, f_sp, c_sp);
		if (s[j] == ' ' && num_exist == false && s[j + 1] == '\0')
			safe_exit_with_splits("Missing numbers", map, f_sp, c_sp);
		if (s[j] >= '0' && s[j] <= '9')
			num_exist = true;
		j++;
	}
}

/* Percorre os 3 canais de cor */
void	colors_check(char **colors, t_map *map, int f_or_c,
			char **f_split, char **c_split)
{
	int	i;

	i = 0;
	while (colors[i])
	{
		check_color_format(colors[i], map, f_split, c_split);
		save_color_values(colors[i], map, f_or_c, i, f_split, c_split);
		i++;
	}
	if (i != 3)
		safe_exit_with_splits("Only 3 numbers are accepted",
			map, f_split, c_split);
}
