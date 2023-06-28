/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:54:11 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/28 14:56:59 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

void	ft_data_change(int key, t_data *data)
{
	t_player *player;

	player = data->player;
	if (key == KEY_D)
		player->xpos++;
	if (key == KEY_A)
		player->xpos--;
	if (key == KEY_S)
		player->ypos++;
	if (key == KEY_W)
		player->ypos--;
	if (key == KEY_RG)
		player->angle += 0.1;
	if (key == KEY_LE)
		player->angle -= 0.1;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
	player->xrot = cos(player->angle);
	player->yrot = sin(player->angle);
}

int	ft_key(int key, t_data *data)
{
	ft_data_change(key, data);
	mlx_clear_window(data->mlx, data->win);
	ft_draw_init(data);
	ft_put_img(data);
	if (key == ESC)
		exit(0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data data;
	char *map = ft_strjoin("map/", av[1]);
	map = ft_strjoin(map, ".cub");
	ft_parse(map, &data);
	data.map->off_map = WIDTH / data.map->xmap;
	ft_init(&data);
	ft_draw_init(&data);
	ft_put_img(&data);
	mlx_hook(data.win, 2, 1L<<0, ft_key, &data);
	mlx_loop(data.mlx);
}
