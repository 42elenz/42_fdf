/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:19:23 by elenz             #+#    #+#             */
/*   Updated: 2021/11/12 00:50:26 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free (split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}

void	free_num_rgb(char *number, char *rgb)
{
	free(number);
	free(rgb);
	rgb = NULL;
	number = NULL;
}

void	ft_free_matrix(t_frame *frame)
{
	int	i;

	i = 0;
	if (frame->matrix[i] != NULL)
	{
		while (frame->matrix[i] != NULL)
		{
			free(frame->matrix[i]);
			frame->matrix[i] = NULL;
			i++;
		}
	}
	free(frame->matrix);
}

void	ft_exit(t_frame *frame)
{
	if (frame->matrix != NULL)
		ft_free_matrix(frame);
	if (frame != NULL)
		free (frame);
	exit(0);
}
