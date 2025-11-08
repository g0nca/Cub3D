/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:16 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/08 16:02:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void print_map_struct(t_cub *cub)
{
    int i = 0;
    while (cub->map->map[i])
    {
        printf("%s\n", cub->map->map[i]);
        i++;
    }
}
int     main(int ac, char **av)
{
    t_cub   *cub;

    cub = malloc(sizeof(t_cub));
    if (!cub)
        return (1);
    parsing_input(ac, av);
    cub->map = read_file_parse(av);
    if (cub->map->exit_flag == 1 || check_elements(cub->map) == false)
    {
        print_error_and_exit_without_free("Loading Elements", 0, cub->map);
        ft_free_all(cub);
        free(cub);
        return (1);
    }
    printf("Map Elements:%s\n", cub->map->no_texture);
    printf("Map Elements:%s\n", cub->map->so_texture);
    printf("Map Elements:%s\n", cub->map->we_texture);
    printf("Map Elements:%s\n", cub->map->ea_texture);
    print_map_struct(cub);
    ft_free_all(cub);
    free(cub);
    return (0);
}
