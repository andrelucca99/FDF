/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:18:45 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/07 14:41:39 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "../gnl/get_next_line.h"

# define BUFFER_SIZE 42
# define WIN_WIDTH 1000
# define WIN_HEIGHT 800

typedef struct s_map
{
	int	**z_matrix;
	int	width;
	int	height;
	int	**colors;
}	t_map;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	t_map	map;
	int		**colors;
}	t_fdf;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
}	t_line;

typedef struct s_render_params
{
	int		scale;
	float	z_factor;
	int		mid_x;
	int		mid_y;
	int		x_offset;
	int		y_offset;
}	t_render_params;

t_map	parse_fdf(char *file);
int		close_window(t_fdf *fdf);
int		key_hook(int keycode, t_fdf *fdf);
int		mouse_hook(int button, int x, int y, void *param);
char	*get_next_line(int fd);
void	free_fdf(t_fdf *fdf);
void	render_map(t_fdf *fdf);
void	free_split(char **split);
void	allocate_z_matrix(t_map *map);
void	get_z_color(char *str, int *z, int *color);
void	draw_line(t_point p0, t_point p1, t_fdf *fdf, int color);

int		ft_abs(int n);
int		is_smaller(int a, int b);
void	project_iso(int *x, int *y, int z);
void	init_line(t_point p0, t_point p1, t_line *line);

int		count_width(char *line);
int		open_fdf_file(char *file);

#endif
