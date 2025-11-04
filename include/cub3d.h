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
#include "../libs/libft/libft.h"
#include "../libs/get_next_line/get_next_line.h"

#define PATH_MAX 4096

typedef struct s_map
{
    char    **map;
    int     width;
    int     height;
}   t_map;


typedef struct s_cub
{
    t_map   *map;
    void    *mlx;
    void    *win;
}   t_cub;

/* typedef struct s_data
{
    int     flag_exit;
    char    *file_path;
}               t_data; */

// free_all.c
void	ft_free_all(t_cub *cub);

// parse/read_file.c
t_map	*read_file_parse(char **av);
t_map	*init_map_struct(void);

// utils/file_utils.c
int	ft_strcmp(const char *s1, const char *s2);

// parsing_input.c
void    parsing_input(int ac, char **av);

// errors.c
void    print_error_and_exit_without_free(const char *message, int exit_flag);

int     main(int ac, char **av);

#endif