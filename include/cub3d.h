/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:40:29 by ggomes-v            #+#    #+#             */
/*   Updated: 2025/11/03 15:40:29 by ggomes-v           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../libft/libft.h"

#define PATH_MAX 4096

typedef struct s_data
{
    int     flag_exit;
    char    *file_path;
}               t_data;


// utils/file_utils.c
int	ft_strcmp(const char *s1, const char *s2);

// parsing_input.c
void    parsing_input(int ac, char **av, t_data *data);

// errors.c
void    print_error_and_exit_without_free(const char *message, int exit_flag);

int     main(int ac, char **av);

#endif