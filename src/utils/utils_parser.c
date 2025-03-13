/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:39:48 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/07 14:40:57 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"

int	count_width(char *line)
{
	int		count;
	char	**values;

	count = 0;
	values = ft_split(line, ' ');
	if (!values)
		return (0);
	while (values[count])
		count++;
	free_split(values);
	return (count);
}

int	open_fdf_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Erro ao abrir o arquivo!");
		exit(1);
	}
	return (fd);
}

void	allocate_z_matrix(t_map *map)
{
	int	i;

	map->z_matrix = (int **)malloc(sizeof(int *) * map->height);
	map->colors = (int **)malloc(sizeof(int *) * map->height);
	if (!map->z_matrix || !map->colors)
	{
		write(2, "Erro ao alocar memória!\n", 25);
		exit(1);
	}
	i = 0;
	while (i < map->height)
	{
		map->z_matrix[i] = NULL;
		map->colors[i] = NULL;
		i++;
	}
}
