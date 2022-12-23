/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:29:27 by elenz             #+#    #+#             */
/*   Updated: 2021/11/11 22:41:14 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	points_in_pixels(t_frame *frame)
{
	int	a;
	int	b;
	int	row;
	int	i;

	row = 0;
	a = frame->sizx / sqrt(pow(frame->rows, 2) + pow(frame->columns, 2));
	b = frame->sizy / sqrt(pow(frame->rows, 2) + pow(frame->columns, 2));
	if (a < b)
		frame->pixelfac = a;
	else
		frame->pixelfac = b;
	while (row < frame->rows)
	{
		i = 0;
		while (i < frame->columns)
		{
			frame->matrix[row][i].x *= frame->pixelfac;
			frame->matrix[row][i].y *= frame->pixelfac;
			i++;
		}
		row++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, t_frame *frame)
{
	char	*dst;

	if (x < frame->sizx && y >= 0 && y < frame->sizy && x >= 0)
	{
		dst = data->addr + (y * data->line_length
				+ x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = frame->rgb_value;
	}
}

void	ft_drawline_x(t_frame *frame)
{
	int	row;
	int	col;

	row = 0;
	while (row < frame->rows)
	{
		col = 0;
		while (col < frame->columns - 1)
		{
			frame->dx = frame->matrix[row][col + 1].x
				- frame->matrix[row][col].x;
			frame->dy = frame->matrix[row][col + 1].y
				- frame->matrix[row][col].y;
			frame->x = frame->matrix[row][col].x;
			frame->y = frame->matrix[row][col].y;
			frame->rgb_value = frame->matrix[row][col].rgb;
			gbham(frame);
			col++;
		}
		row++;
	}
}

void	ft_drawline_y(t_frame *frame)
{
	int	row;
	int	col;

	col = 0;
	while (col < frame->columns)
	{
		row = 0;
		while (row < frame->rows - 1)
		{
			frame->dx = frame->matrix[row + 1][col].x
				- frame->matrix[row][col].x;
			frame->dy = frame->matrix[row + 1][col].y
				- frame->matrix[row][col].y;
			frame->x = frame->matrix[row][col].x;
			frame->y = frame->matrix[row][col].y;
			frame->rgb_value = frame->matrix[row][col].rgb;
			gbham(frame);
			row++;
		}
		col++;
	}
}

void	draw_mash(t_frame *frame)
{
	points_in_pixels(frame);
	get_z_factor(frame);
	pixels_to_isometric(frame);
	ft_drawline_x(frame);
	ft_drawline_y(frame);
	mlx_put_image_to_window(frame->mlx_ptr, frame->win_ptr,
		frame->img.img, 0, 0);
	mlx_destroy_image(frame->mlx_ptr, frame->img.img);
}
