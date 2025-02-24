/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:50:18 by alucas-e          #+#    #+#             */
/*   Updated: 2025/02/24 18:07:01 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static	int	get_z_value(char *str)
{
	char	**split;
	int		z_value;

	split = ft_split(str, ',');
	if (!split || !split[0])
		return (0);
	z_value = ft_atoi(split[0]);
	free_split(split);
	return (z_value);
}

static	int	count_width(char *line)
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

static int	open_fdf_file(char *file)
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

static void	get_map_dimensions(char *file, t_map *map)
{
	int		fd;
	char	*line;

	fd = open_fdf_file(file);
	map->height = 0;
	while ((line = get_next_line(fd)))
	{
		if (map->height == 0)
			map->width = count_width(line);
		map->height++;
		free(line);
	}
	close(fd);

	if (map->height == 0 || map->width == 0)
	{
		write(2, "Erro: Arquivo .fdf vazio ou inválido!\n", 37);
		exit(1);
	}
}

static void	allocate_z_matrix(t_map *map)
{
	map->z_matrix = (int **)malloc(sizeof(int *) * map->height);
	if (!map->z_matrix)
	{
		write(2, "Erro ao alocar memória!\n", 25);
		exit(1);
	}
}

static void	parse_fdf_line(t_map *map, char *line, int row)
{
	char	**values;
	int		j;

	values = ft_split(line, ' ');
	if (!values)
	{
		write(2, "Erro: Falha ao dividir a linha!\n", 32);
		exit(1);
	}

	map->z_matrix[row] = (int *)malloc(sizeof(int) * map->width);
	if (!map->z_matrix[row])
	{
		write(2, "Erro: Falha ao alocar linha do mapa!\n", 37);
		free_split(values);
		exit(1);
	}
	j = 0;
	while (j < map->width)
	{
		if (!values[j])
		{
			write(2, "Erro: Formato do .fdf inválido!\n", 33);
			free_split(values);
			exit(1);
		}
		// map->z_matrix[row][j] = ft_atoi(values[j]);
		map->z_matrix[row][j] = get_z_value(values[j]);
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

// t_map	parse_fdf(char *file)
// {
// 	t_map	map;
// 	int		fd;
// 	int		i;
// 	char	*line;

// 	fd = open(file, O_RDONLY);
// 	i = 0;

// 	if (fd < 0)
// 	{
// 		perror("Erro ao abrir o arquivo");
// 		exit(1);
// 	}

// 	map.height = 0;
// 	map.width = 0;
// 	while ((line = get_next_line(fd)))
// 	{
// 		if (map.height == 0)
// 			map.width = count_width(line);

// 		map.height++;
// 		free(line);
// 	}
// 	close(fd);

// 	if (map.height == 0 || map.width == 0)
// 	{
// 		write(2, "Erro: Arquivo .fdf vazio ou inválido!\n", 37);
// 		exit(1);
// 	}

// 	map.z_matrix = (int **)malloc(sizeof(int *) * map.height);
// 	if (!map.z_matrix)
// 	{
// 		write(2, "Erro ao alocar memória!\n", 25);
// 		exit(1);
// 	}

// 	fd = open(file, O_RDONLY);
// 	i = 0;
// 	while ((line = get_next_line(fd)))
// 	{
// 		char	**values;

// 		values = ft_split(line, ' ');

// 		if (!values)
// 		{
// 			write(2, "Erro: Falha ao dividir a linha!\n", 32);
// 			exit(1);
// 		}

// 		map.z_matrix[i] = (int *)malloc(sizeof(int) * map.width);
// 		if (!map.z_matrix[i])
// 		{
// 			write(2, "Erro: Falha ao alocar linha do mapa!\n", 37);
// 			free_split(values);
// 			exit(1);
// 		}

// 		for (int j = 0; j < map.width; j++)
// 		{
// 			if (values[j] == NULL)
// 			{
// 				write(2, "Erro: Formato do .fdf inválido!\n", 33);
// 				free_split(values);
// 				exit(1);
// 			}
// 			map.z_matrix[i][j] = ft_atoi(values[j]);
// 		}
// 		free_split(values);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (map);
// }
