/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:53:27 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/11/04 15:52:28 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free_all(t_cub *cub)
{
	int		i;

	i = 0;
	while (cub->map->map[i])
	{
		free(cub->map->map[i]);
		i++;
	}
	free(cub->map->map);
	free(cub->map);
}