/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:07 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/26 16:30:24 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_square(t_data *data, int xpos, int ypos, int color, int size)
{
	int	tmp_col = color;

	for (int i = 0; i < size;i++)
	{
		for(int j = 0; j < size; j++)
		{
			if ((j + 1) == size || (i + 1) == size)
				color = GRID;
			ft_put_pix(i + xpos, j+ypos, color, data);
			color = tmp_col;
		}
	}
}

// void	ft_draw_map(t_data *data)
// {

// 	int color, i, j;
// 	color = 0;
// 	i = 0;
// 	j = 0;

// 	while (i < xmap)
// 	{
// 		j = 0;
// 		while (j < ymap)
// 		{
// 			if (map[(j * ymap) + i] == 1)
// 				color = WALL;
// 			else
// 				color = FLOOR;
// 			ft_draw_square(data, i *  off_map , j *  off_map, color, off_map);
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	ft_background(t_data *data)
{
	for(int	i= 0; i < WIDTH ;i++)
		for(int j =0; j < HEIGHT; j++)
			ft_put_pix(i, j , 0x00, data);
}
