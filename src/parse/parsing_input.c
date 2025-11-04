/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:08:22 by marvin            #+#    #+#             */
/*   Updated: 2025/11/03 16:08:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void parsing_input(int ac, char **av, t_data *data)
{
    (void)av;
    (void)data;
    if (ac != 2)
        print_error_and_exit_without_free("Invalid number of arguments.");
    if (av[1][0] == '\0')
        print_error_and_exit_without_free("Empty File Name");
    if (ft_strlen(av[1]) > PATH_MAX)
        print_error_and_exit_without_free("Long Path is invalid");    
}
