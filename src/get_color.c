/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_z_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:18:45 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/07 14:40:49 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	hex_to_int(const char *hex)
{
	int	result;
	int	i;

	result = 0;
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		i = 2;
	else
		i = 0;
	while (hex[i])
	{
		result *= 16;
		if (hex[i] >= '0' && hex[i] <= '9')
			result += hex[i] - '0';
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			result += hex[i] - 'a' + 10;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			result += hex[i] - 'A' + 10;
		else
			return (0xFFFFFFFF);
		i++;
	}
	return (result);
}

static int	get_color(char *str)
{
	char	**split;
	int		color;

	split = ft_split(str, ',');
	color = 0xFFFFFFFF;
	if (split && split[1])
	{
		color = hex_to_int(split[1]);
		if (color <= 0xFFFFFF)
			color |= 0xFF000000;
	}
	free_split(split);
	return (color);
}

static int	get_z(char *str)
{
	char	**split;
	int		z;

	split = ft_split(str, ',');
	if (!split || !split[0])
	{
		free_split(split);
		return (0);
	}
	z = ft_atoi(split[0]);
	free_split(split);
	return (z);
}

void	get_z_color(char *str, int *z, int *color)
{
	*z = get_z(str);
	*color = get_color(str);
}
