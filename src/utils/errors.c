/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:23 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/04 14:16:01 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    print_error_and_exit_without_free(const char *message, int exit_flag)
{
    printf("Error : %s\n", message);
    if (exit_flag == 1)
        exit(EXIT_FAILURE);
}

void    print_error_and_exit(const char *msg)
{
    write(2, "Error\n", 6);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    exit(1);
}
