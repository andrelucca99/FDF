/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:50:18 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/06 16:44:46 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	get_map_dimensions(char *file, t_map *map)
{
	int		fd;
	char	*line;

	fd = open_fdf_file(file);
	map->height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (map->height == 0)
			map->width = count_width(line);
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (map->height == 0 || map->width == 0)
	{
		write(2, "Erro: Arquivo .fdf vazio ou inválido!\n", 37);
		exit(1);
	}
}

static	void	allocate_map_row(t_map *map, int row)
{
	map->z_matrix[row] = (int *)malloc(sizeof(int) * map->width);
	map->colors[row] = (int *)malloc(sizeof(int) * map->width);
	if (!map->z_matrix[row] || !map->colors[row])
	{
		write(2, "Erro: Falha ao alocar linha do mapa!\n", 37);
		exit(1);
	}
}

static void	parse_fdf_line(t_map *map, char *line, int row)
{
	char	**values;
	int		j;
	int		z;
	int		color;

	values = ft_split(line, ' ');
	if (!values)
	{
		write(2, "Erro: Falha ao dividir a linha!\n", 32);
		exit(1);
	}
	allocate_map_row(map, row);
	j = 0;
	while (j < map->width)
	{
		get_z_color(values[j], &z, &color);
		map->z_matrix[row][j] = z;
		map->colors[row][j] = color;
		j++;
	}
	free_split(values);
}

t_map	parse_fdf(char *file)
{
	t_map	map;
	int		fd;
	int		i;
	char	*line;

	i = 0;
	get_map_dimensions(file, &map);
	allocate_z_matrix(&map);
	fd = open_fdf_file(file);
	line = get_next_line(fd);
	while (line != NULL)
	{
		parse_fdf_line(&map, line, i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (map);
}
