/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:34:53 by elenz             #+#    #+#             */
/*   Updated: 2021/11/12 00:54:30 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_frame	*init_frame(t_frame *frame, char **argv)
{
	frame = (t_frame *)malloc(1 * sizeof(t_frame));
	if (frame == NULL)
		exit(0);
	frame->mlx_ptr = mlx_init();
	if (frame->mlx_ptr == NULL)
		ft_error_1(frame, 1);
	frame->rows = 0;
	frame->columns = 0;
	frame->sizx = 2560;
	frame->sizy = 1600;
	frame->img.img = mlx_new_image(frame->mlx_ptr, 2560, 1600);
	if (frame->img.img == NULL)
		ft_error_1(frame, 1);
	frame->win_ptr = mlx_new_window(frame ->mlx_ptr, 2560, 1600, "mlx");
	if (frame->win_ptr == NULL)
		ft_error_1(frame, 2);
	frame->img.addr = mlx_get_data_addr(frame->img.img,
			&frame->img.bits_per_pixel, &frame->img.line_length,
			&frame->img.endian);
	frame->argv = argv;
	frame->fd = open(frame->argv[1], O_RDONLY);
	if (frame->fd == -1)
		ft_error(frame);
	frame->matrix = NULL;
	return (frame);
}

void	get_z_factor(t_frame *frame)
{
	int	diff;
	int	quot;

	quot = frame->columns / frame->rows;
	diff = frame->z_max - frame->z_min;
	if (diff != 0)
		frame->z_factor = 100 / diff;
	if (frame->z_factor == 0 || diff == 0)
		frame->z_factor = 1;
}
