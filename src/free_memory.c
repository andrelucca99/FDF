/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:02:42 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/06 16:46:17 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_map(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->z_matrix)
		{
			i = 0;
			while (i < map->height)
			{
				free(map->z_matrix[i]);
				free(map->colors[i]);
				i++;
			}
			free(map->z_matrix);
			free(map->colors);
		}
	}
}

void	free_fdf(t_fdf *fdf)
{
	if (fdf)
	{
		free_map(&fdf->map);
		if (fdf->mlx && fdf->win)
			mlx_destroy_window(fdf->mlx, fdf->win);
		if (fdf->mlx)
		{
			mlx_destroy_display(fdf->mlx);
			free(fdf->mlx);
		}
	}
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
