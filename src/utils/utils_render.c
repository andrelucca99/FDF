/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:25:51 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/06 16:43:39 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fdf.h"
#include <math.h>

void	project_iso(int *x, int *y, int z)
{
	int	prev_x;
	int	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.523599);
	*y = (prev_x + prev_y) * sin(0.523599) - z;
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	is_smaller(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}

void	init_line(t_point p0, t_point p1, t_line *line)
{
	line->dx = ft_abs(p1.x - p0.x);
	line->dy = ft_abs(p1.y - p0.y);
	line->sx = is_smaller(p0.x, p1.x);
	line->sy = is_smaller(p0.y, p1.y);
	line->err = line->dx - line->dy;
}
