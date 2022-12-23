/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   estab_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:10:38 by elenz             #+#    #+#             */
/*   Updated: 2021/11/12 00:26:18 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_get_size_matrix(t_frame *frame)
{
	char	*s;
	int		i;
	char	**split_line;

	i = 0;
	s = get_next_line(frame->fd, 60);
	if (s == NULL)
		ft_error(frame);
	split_line = ft_split(s, ' ');
	while (split_line[i] != NULL)
	{
		if (split_line[i][0] != '\n')
			frame->columns += 1;
		i++;
	}
	while (s != NULL)
	{
		if (s[0] != '\n')
			frame->rows += 1;
		free(s);
		s = get_next_line(frame->fd, i);
	}
	close(frame->fd);
	ft_free_split(split_line);
}

void	alloc_matrix(t_frame *frame)
{
	int	i;

	i = 0;
	frame->matrix = (t_point **) ft_calloc(sizeof(t_point *),
			(frame->rows + 1));
	if (frame->matrix == NULL)
		ft_error(frame);
	while (i < frame->rows)
	{
		frame->matrix[i] = (t_point *) ft_calloc(sizeof(t_point),
				(frame->columns + 1));
		if (frame->matrix[i] == NULL)
			ft_error(frame);
		i++;
	}
	frame->matrix[frame->rows] = NULL;
}

void	get_z_and_rgb(t_frame *frame, char *string)
{
	int		i;
	char	*number;
	char	*rgb;
	int		f;

	i = 0;
	f = 0;
	number = string;
	rgb = "0x00FFFFFF";
	while (string != NULL && string[i] != '\0')
	{
		if (string[i] == ',')
		{
			number = ft_substr(string, 0, i);
			rgb = ft_substr(string, i + 1, ft_strlen(string));
			f = 1;
			break ;
		}
		i++;
	}
	frame->z_value = ft_atoi(number);
	frame->rgb_value = hex2int(rgb);
	if (f == 1)
		free_num_rgb(number, rgb);
}

void	fill_point(t_frame *frame, char **s, int row, char *g_s)
{
	int	i;

	i = 0;
	while (i < frame->columns)
	{
		if (s[i] == NULL)
		{
			ft_free_split(s);
			free(g_s);
			ft_error(frame);
		}
		get_z_and_rgb(frame, s[i]);
		frame->matrix[row][i].z = frame->z_value;
		frame->matrix[row][i].x = i;
		frame->matrix[row][i].y = row;
		if (frame->rgb_value == 0x00FFFFFF && frame->z_value != 0)
			frame->rgb_value = 0x000FFF00 - frame->z_value * 6000;
		if (frame->z_max < frame->z_value)
			frame->z_max = frame->z_value;
		if (frame->z_min > frame->z_value)
			frame->z_min = frame->z_value;
		frame->matrix[row][i].rgb = frame->rgb_value;
		i++;
	}
}

void	fill_matrix(t_frame *frame)
{
	char	*s;
	char	**split_line;
	int		row;

	row = 0;
	frame->z_max = 0;
	frame->z_min = 0;
	frame->pixelcount = 0;
	frame->fd = open(frame->argv[1], O_RDONLY);
	if (frame->fd == -1)
		ft_error(frame);
	while (row < frame->rows)
	{
		s = get_next_line(frame->fd, frame->columns);
		split_line = ft_split(s, ' ');
		fill_point(frame, split_line, row, s);
		row++;
		free(s);
		ft_free_split(split_line);
	}
	close(frame->fd);
}
