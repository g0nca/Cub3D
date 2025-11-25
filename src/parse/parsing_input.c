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

static void	check_extension(int ac, char **av);
static void	check_permissions(char **av);

void	parsing_input(int ac, char **av)
{
	check_extension(ac, av);
	check_permissions(av);
}

static void	check_permissions(char **av)
{
	struct stat	info;

	if (access(av[1], F_OK) == -1)
		print_error_and_exit_without_free("File doesn't exists", 1, NULL);
	if (access(av[1], R_OK) == -1)
		print_error_and_exit_without_free("Without Read Permissions", 1, NULL);
	if (stat(av[1], &info) == -1)
	{
		perror("stat");
		return ;
	}
	if (S_ISDIR(info.st_mode))
		print_error_and_exit_without_free("Is a Directory", 1, NULL);
}

static void	check_extension(int ac, char **av)
{
	int	len;

	if (ac != 2)
		print_error_and_exit_without_free(
			"Invalid number of arguments.", 1, NULL);
	len = ft_strlen(av[1]);
	if (av[1][0] == '\0')
		print_error_and_exit_without_free("Empty File Name", 1, NULL);
	if (ft_strlen(av[1]) > PATH_MAX)
		print_error_and_exit_without_free("Long Path is invalid", 1, NULL);
	if (av[1][0] == '.')
		print_error_and_exit_without_free("Invalid file name", 1, NULL);
	if (len < 5)
		print_error_and_exit_without_free("Invalid file name", 1, NULL);
	if (ft_strcmp(&av[1][len - 4], ".cub") != 0)
		print_error_and_exit_without_free(
			"Invalid file extension \"Example.cub\"", 1, NULL);
}
