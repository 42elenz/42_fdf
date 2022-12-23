/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:05:24 by elenz             #+#    #+#             */
/*   Updated: 2021/11/12 00:56:11 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	define_matrix(t_frame *frame)
{
	ft_get_size_matrix(frame);
	alloc_matrix(frame);
	fill_matrix(frame);
}

int	ft_close(int keycode, void *temp_frame)
{
	t_frame	*frame;

	frame = (t_frame *) temp_frame;
	if (keycode == 53)
	{
		mlx_destroy_window(frame->mlx_ptr, frame->win_ptr);
		ft_exit(frame);
		return (0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_frame	*frame;
	int		fd;

	frame = NULL;
	if (argc == 1)
	{
		write(2, "Enter map", 9);
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "No file", 7);
		exit(0);
	}
	close(fd);
	frame = init_frame(frame, argv);
	define_matrix(frame);
	draw_mash(frame);
	mlx_key_hook(frame->win_ptr, ft_close, frame);
	mlx_loop(frame->mlx_ptr);
	return (0);
}
