/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:02:27 by alucas-e          #+#    #+#             */
/*   Updated: 2025/02/24 18:14:33 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <math.h>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 800

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

void	draw_line(t_point p0, t_point p1, t_fdf *fdf, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = ft_abs(p1.x - p0.x);
	dy = ft_abs(p1.y - p0.y);

	sx = is_smaller(p0.x, p1.x);
	sy = is_smaller(p0.y, p1.y);

	err = dx - dy;

	while (p0.x != p1.x || p0.y != p1.y)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, p0.x, p0.y, color);
		e2 = 2 * err;

		if (e2 > -dy)
		{
			err -= dy;
			p0.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			p0.y += sy;
		}
	}
}

void	render_map(t_fdf *fdf)
{
	int x_offset, y_offset;
	int mid_x, mid_y;
	int scale_x, scale_y, scale;
	float	z_factor;

	scale_x = WIN_WIDTH / (fdf->map.width + 2);
	scale_y = WIN_HEIGHT / (fdf->map.height + 2);
	scale = (scale_x < scale_y) ? scale_x : scale_y;
	if (scale < 5)
		scale = 5;

	z_factor = ((float)scale / 5);
	if (z_factor < 1)
		z_factor = 1;

	mid_x = (fdf->map.width * scale) / 2;
	mid_y = (fdf->map.height * scale) / 2;

	x_offset = WIN_WIDTH / 2;
	y_offset = WIN_HEIGHT / 2;

	for (int y = 0; y < fdf->map.height; y++)
	{
		for (int x = 0; x < fdf->map.width; x++)
		{
			t_point p0;
			p0.x = (x * scale) - mid_x;
			p0.y = (y * scale) - mid_y;
			// int z = fdf->map.z_matrix[y][x] * (scale / 4);
			int z = fdf->map.z_matrix[y][x] * z_factor;
			project_iso(&p0.x, &p0.y, z);
			p0.x += x_offset;
			p0.y += y_offset;

			if (x + 1 < fdf->map.width)
			{
				t_point p1;
				p1.x = ((x + 1) * scale) - mid_x;
				p1.y = (y * scale) - mid_y;
				int z1 = fdf->map.z_matrix[y][x + 1] * z_factor;
				project_iso(&p1.x, &p1.y, z1);
				p1.x += x_offset;
				p1.y += y_offset;

				draw_line(p0, p1, fdf, 0xFFFFFF);
			}

			if (y + 1 < fdf->map.height)
			{
				t_point p1;
				p1.x = (x * scale) - mid_x;
				p1.y = ((y + 1) * scale) - mid_y;
				int z1 = fdf->map.z_matrix[y + 1][x] * z_factor;
				project_iso(&p1.x, &p1.y, z1);
				p1.x += x_offset;
				p1.y += y_offset;

				draw_line(p0, p1, fdf, 0xFFFFFF);
			}
		}
	}
}
