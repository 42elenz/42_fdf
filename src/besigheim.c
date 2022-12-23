/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   besigheim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 00:38:54 by elenz             #+#    #+#             */
/*   Updated: 2021/11/11 17:34:48 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	sgn(int x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	if (x == 0)
		return (0);
	return (0);
}

void	get_values_besig(t_frame *frame)
{
	frame->incx = sgn(frame->dx);
	frame->incy = sgn(frame->dy);
	if (frame->dx < 0)
		frame->dx = -frame->dx;
	if (frame->dy < 0)
		frame->dy = -frame->dy;
	if (frame->dx > frame->dy)
	{
		frame->pdx = frame->incx;
		frame->pdy = 0;
		frame->ddx = frame->incx;
		frame->ddy = frame->incy;
		frame->dslowdir = frame->dy;
		frame->dfastdir = frame->dx;
	}
	else
	{
		frame->pdx = 0;
		frame->pdy = frame->incy;
		frame->ddx = frame->incx;
		frame->ddy = frame->incy;
		frame->dslowdir = frame->dx;
		frame->dfastdir = frame->dy;
	}
}

void	pixelcount(t_frame *frame)
{
	int	t;

	t = 0;
	get_values_besig(frame);
	frame->p = frame->dfastdir / 2;
	while (t < frame->dfastdir)
	{
		frame->p -= frame->dslowdir;
		if (frame->p < 0)
		{
			frame->p += frame->dfastdir;
			frame->x += frame->ddx;
			frame->y += frame->ddy;
		}
		else
		{
			frame->x += frame->pdx;
			frame->y += frame->pdy;
			frame->pixelcount++;
		}
		t++;
	}
}

void	gbham(t_frame *frame)
{
	int	t;

	t = 0;
	get_values_besig(frame);
	frame->p = frame->dfastdir / 2;
	my_mlx_pixel_put(&frame->img, frame->x, frame->y, frame);
	while (t < frame->dfastdir)
	{
		frame->p -= frame->dslowdir;
		if (frame->p < 0)
		{
			frame->p += frame->dfastdir;
			frame->x += frame->ddx;
			frame->y += frame->ddy;
		}
		else
		{
			frame->x += frame->pdx;
			frame->y += frame->pdy;
			frame->pixelcount++;
		}
		my_mlx_pixel_put(&frame->img, frame->x, frame->y, frame);
		t++;
	}
}
