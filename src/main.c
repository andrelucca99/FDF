/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:08:25 by alucas-e          #+#    #+#             */
/*   Updated: 2025/03/07 15:03:12 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
	{
		write (1, "Uso: ./fdf <mapa.fdf>\n", 22);
		return (1);
	}
	fdf.map = parse_fdf(argv[1]);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1524, 768, "FDF");
	mlx_key_hook(fdf.win, key_hook, &fdf);
	mlx_hook(fdf.win, 17, 0, close_window, &fdf);
	render_map(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
