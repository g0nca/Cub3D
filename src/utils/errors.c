/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/07 13:38:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    print_error_and_exit_without_free(const char *message, int exit_flag, t_map *map)
{
    printf("Error : %s\n", message);
    if (exit_flag == 1)
        exit(EXIT_FAILURE);
    map->exit_flag = 1;
}
