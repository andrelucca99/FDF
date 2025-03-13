/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:02:27 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/07 15:03:24 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_line(t_point p0, t_point p1, t_fdf *fdf, int color)
{
	t_line	line;
	int		e2;

	if ((color & 0xFF000000) == 0x00000000)
		return ;
	init_line(p0, p1, &line);
	while (p0.x != p1.x || p0.y != p1.y)
	{
		mlx_pixel_put(fdf->mlx, fdf->win, p0.x, p0.y, color);
		e2 = 2 * line.err;
		if (e2 > -line.dy)
		{
			line.err -= line.dy;
			p0.x += line.sx;
		}
		if (e2 < line.dx)
		{
			line.err += line.dx;
			p0.y += line.sy;
		}
	}
}

void	setup_render_params(t_fdf *fdf, t_render_params *params)
{
	int	scale_x;
	int	scale_y;

	scale_x = WIN_WIDTH / (fdf->map.width + 1.5);
	scale_y = WIN_HEIGHT / (fdf->map.height + 1.5);
	if (scale_x < scale_y)
		params->scale = scale_x;
	else
		params->scale = scale_y;
	if (params->scale < 5)
		params->scale = 5;
	params->z_factor = ((float)params->scale / 2);
	if (params->z_factor < 1)
		params->z_factor = 1;
	params->mid_x = (fdf->map.width * params->scale) / 1.5;
	params->mid_y = (fdf->map.height * params->scale) / 1.5;
	params->x_offset = WIN_WIDTH / 1.5;
	params->y_offset = WIN_HEIGHT / 1.5;
}

static	t_point	get_projected_point(
	int x, int y, int z, t_render_params *params)
{
	t_point	p;

	p.x = (x * params->scale) - params->mid_x;
	p.y = (y * params->scale) - params->mid_y;
	project_iso(&p.x, &p.y, z * params->z_factor);
	p.x += params->x_offset;
	p.y += params->y_offset;
	return (p);
}

void	render_point(t_fdf *fdf, int x, int y, t_render_params *params)
{
	t_point	p0;
	int		color;

	p0 = get_projected_point(x, y, fdf->map.z_matrix[y][x], params);
	color = fdf->map.colors[y][x];
	if (x + 1 < fdf->map.width)
		draw_line(
			p0, get_projected_point(
				x + 1, y, fdf->map.z_matrix[y][x + 1], params), fdf, color);
	if (y + 1 < fdf->map.height)
		draw_line(
			p0, get_projected_point(
				x, y + 1, fdf->map.z_matrix[y + 1][x], params), fdf, color);
}

void	render_map(t_fdf *fdf)
{
	t_render_params	params;
	int				y;
	int				x;

	setup_render_params(fdf, &params);
	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			render_point(fdf, x, y, &params);
			x++;
		}
		y++;
	}
}
