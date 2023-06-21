/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:15 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/21 17:25:52 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pix(int x, int y, int color,t_data *data)
{
	t_img	*img;
	char	*addr;

	img= data->img;
	addr = img->addr + ((y * img->line_len) + (x * img->bpp/8));
	*(int *)addr = color;
}

void	ft_put_img(t_data *data)
{
	mlx_put_image_to_window(data->mlx,data->win,data->img->img_ptr, 0,0);
}
