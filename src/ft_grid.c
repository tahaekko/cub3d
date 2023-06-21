/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:07 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/21 17:25:08 by msamhaou         ###   ########.fr       */
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

void	ft_background(t_data *data)
{
	for(int	i= 0; i < WIDTH ;i++)
		for(int j =0; j < HEIGHT; j++)
			ft_put_pix(i, j , 0x00, data);
}
