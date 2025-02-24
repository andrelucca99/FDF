/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas-e <alucas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:48:30 by alucas-e          #+#    #+#             */
/*   Updated: 2025/02/21 15:52:57 by alucas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
	{
		free_fdf(fdf);
		exit(0);
	}
	return (0);
}

int	close_window(t_fdf *fdf)
{
	free_fdf(fdf);
	exit(0);
}
