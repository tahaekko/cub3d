/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:10 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/28 14:54:52 by taha             ###   ########.fr       */
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
	player->height = 5;
	player->width = 5;
	player->xpos = WIDTH / GRID  * 1;
	player->ypos = HEIGHT / GRID * 2;
	player->angle = 30 * 0.0174533;
	player->xrot = cos(player->angle);
	player->yrot = sin(player->angle);
}

void	ft_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx,WIDTH, HEIGHT, "ZEB!");
	ft_init_img(data);
	ft_player_init(data->player);
}
void	ft_draw_direction(t_data *data)
{
	t_player	*player;
	int			i;

	i = 0;
	player = data->player;
	while (i <  20)
	{
		ft_put_pix(player->xpos + i * player->xrot, player->ypos + i * player->yrot, 0x00FF00, data);
		i++;
	}
}

void	ft_draw_init(t_data *data)
{
	t_player	*player = data->player;
	ft_draw_map(data);
	ft_draw_square(data, player->xpos, player->ypos, 0x0ef0e5, player->height);
	ft_draw_direction(data);
	ft_put_img(data);
}
