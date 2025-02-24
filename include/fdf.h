/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:18:45 by alucas-e          #+#    #+#             */
/*   Updated: 2025/02/21 15:25:58 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <stdio.h>

#define BUFFER_SIZE 42

typedef struct s_map
{
	int **z_matrix;
	int width;
	int height;
} t_map;

typedef struct s_fdf
{
	void *mlx;
	void *win;
	t_map map;
} t_fdf;

typedef struct s_point
{
	int x;
	int y;
} t_point;

int	key_hook(int keycode, t_fdf *fdf);
int	mouse_hook(int button, int x, int y, void *param);
int	close_window(t_fdf *fdf);

t_map parse_fdf(char *file);
void render_map(t_fdf *fdf);
// void draw_line(int x0, int y0, int x1, int y1, t_fdf *fdf, int color);
void	draw_line(t_point p0, t_point p1, t_fdf *fdf, int color);
char	*get_next_line(int fd);
void	free_fdf(t_fdf *fdf);
void free_split(char **split);

#endif
