/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:16 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/07 14:34:11 by marvin           ###   ########.fr       */
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
    if (cub->map->exit_flag == 1)
    {
        ft_free_all(cub);
        free(cub);
        return (1);
    }
    print_map_struct(cub);
    ft_free_all(cub);
    free(cub);
    printf("FEITO\n");
    return (0);
}