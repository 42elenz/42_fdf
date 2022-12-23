/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_to_iso.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 22:40:27 by elenz             #+#    #+#             */
/*   Updated: 2021/11/11 23:48:21 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	pixels_to_isometric(t_frame *frame)
{
	int		row;
	int		i;
	double	x;
	double	y;
	double	z;

	row = 0;
	while (row < frame->rows)
	{
		i = 0;
		while (i < frame->columns)
		{
			x = frame->matrix[row][i].x - frame->columns / 2 * frame->pixelfac;
			y = frame->matrix[row][i].y - frame->rows / 2 * frame->pixelfac;
			z = frame->matrix[row][i].z * frame->z_factor;
			frame->matrix[row][i].x = (x * cos(M_PI / 6))
				+ (y * cos(M_PI / 1.2)) + (z * cos(-M_PI_2 / 2))
				+ (frame->sizx / 2);
			frame->matrix[row][i].y = (x * sin(M_PI / 6))
				+ (y * sin(M_PI / 1.2)) + (z * sin(-M_PI_2 / 2))
				+ (frame->sizy / 2);
			i++;
		}
		row++;
	}
}
