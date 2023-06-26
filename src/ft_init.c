/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:10 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/26 16:36:48 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_img(t_data *data)
{
	t_img *img = data->img;

	img->img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line, &img->endian);
}

static void	ft_player_init(t_player *player)
{
	player->xpos = WIDTH / GRID  * 1;
	player->ypos = HEIGHT / GRID * 2;
	player->angle = 30 * 0.0174533;
}

void	ft_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx,WIDTH, HEIGHT, "ZEB!");
	ft_init_img(data);
	ft_player_init(data->player);
}
void	ft_draw_init(t_data *data)
{
	t_player	*player = data->player;
	ft_draw_square(data, player->xpos, player->ypos, 0x0ef0e5, 20);
	ft_put_img(data);
}
