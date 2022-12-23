/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 00:50:33 by elenz             #+#    #+#             */
/*   Updated: 2021/11/12 01:02:13 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_error(t_frame *frame)
{
	if (frame->matrix != NULL)
		ft_free_matrix(frame);
	if (frame != NULL)
		free(frame);
	if (frame->mlx_ptr != NULL && frame->img.img != NULL)
		mlx_destroy_image(frame->mlx_ptr, frame->img.img);
	write(2, "ERROR", 5);
	exit(0);
}

void	ft_error_1(t_frame *frame, int level)
{
	if (level == 2)
		mlx_destroy_image(frame->mlx_ptr, frame->img.img);
	write(2, "ERROR", 5);
	free(frame);
	exit(0);
}
