/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:10 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/21 17:25:11 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_img(t_data *data)
{
	t_img *img = data->img;

	img->img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len, &img->endian);
}

void	ft_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx,WIDTH, HEIGHT, "ZEB!");
	data->img = malloc(sizeof(t_img));
	ft_init_img(data);
}

