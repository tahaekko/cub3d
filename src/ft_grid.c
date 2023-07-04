/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:07 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/01 12:23:22 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_draw_square(t_data *data, int xpos, int ypos, int color, int size)
{
	int tmp_col = color;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((j + 1) == size || (i + 1) == size)
				color = GRID_C;
			ft_put_pix(i + xpos, j + ypos, color, data);
			color = tmp_col;
		}
	}
}

void ft_draw_map(t_data *data)
{

	int color, i, j;
	color = 0;
	i = 0;
	j = 0;

	while (i < data->map->ymap)
	{
		j = 0;
		while (j < data->map->xmap)
		{
			if (data->map->map_compo[(i * data->map->xmap) + j] == 1)
				color = WALL;
			else if (data->map->map_compo[(i * data->map->xmap) + j] == 0)
				color = FLOOR;
			else
				color = 0;
			ft_draw_square(data, j *  data->map->off_map, i *  data->map->off_map, color, data->map->off_map);
			j++;
		}
		i++;
	}
}

void ft_background(t_data *data)
{
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			ft_put_pix(i, j, 0x00, data);
}
