/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 22:55:47 by elenz             #+#    #+#             */
/*   Updated: 2021/11/12 00:52:20 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		rgb;
}	t_point;

typedef struct whole_struct
{
	t_data	img;
	t_point	**matrix;
	int		sizx;
	int		sizy;
	int		rows;
	int		columns;
	int		fd;
	char	**argv;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*win_img;
	int		dx;
	int		dy;
	int		incx;
	int		incy;
	double	x;
	double	y;
	int		z_value;
	int		rgb_value;
	int		pdx;
	int		pdy;
	int		ddx;
	int		ddy;
	int		dslowdir;
	int		dfastdir;
	double	p;
	int		pixelfac;
	int		z_factor;
	int		z_max;
	int		z_min;
	int		pixelcount;
}	t_frame;

void			ft_get_size_matrix(t_frame *frame);
void			alloc_matrix(t_frame *frame);
void			fill_matrix(t_frame *frame);
void			get_z_factor(t_frame *frame);
void			draw_mash(t_frame *frame);
t_frame			*init_frame(t_frame *frame, char **argv);
void			gbham(t_frame *frame);
void			pixels_to_isometric(t_frame *frame);
void			my_mlx_pixel_put(t_data *data, int x, int y, t_frame *frame);
void			ft_error(t_frame *frame);
void			ft_error_1(t_frame *frame, int level);
void			free_num_rgb(char *number, char *rgb);
void			ft_free_split(char **split);
void			ft_free_matrix(t_frame *frame);
void			ft_exit(t_frame *frame);
#endif