/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:54:11 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/14 06:50:03 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int g_var;

void	ft_data_change(int key, t_data *data)
{
	t_player *player;

	player = data->player;
	if (key == KEY_UP)
		g_var++;
	if (key == KEY_DN)
		g_var--;
	if (key == KEY_D)
		player->xpos++;
	if (key == KEY_A)
		player->xpos--;
	if (key == KEY_S)
	{
		player->xpos -= player->xrot;
		player->ypos -= player->yrot;
	}
	if (key == KEY_W)
	{
		player->xpos += player->xrot;
		player->ypos += player->yrot;
	}
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
	player->point->x = player->xpos;
	player->point->y = player->ypos;
}

int	ft_key(int key, t_data *data)
{
	ft_data_change(key, data);
	mlx_clear_window(data->mlx, data->win);
	ft_draw_init(data);
	ft_put_img(data);
	// ft_coordinante(data);
	if (key == ESC)
		exit(0);
	return (0);
}

void	ft_coordinante(t_data *data)
{
	int i = 0;
	while (i < data->map->ymap)
	{
		mlx_string_put(data->mlx, data->win, data->map->off_map * data->map->xmap, data->map->off_map * i, 0x00FF00 ,ft_itoa(i * data->map->off_map));
		i++;
	}
	i = 0;
	while (i < data->map->xmap)
	{
		mlx_string_put(data->mlx, data->win, data->map->off_map * i, data->map->off_map * data->map->ymap, 0x00FF00 ,ft_itoa(i * data->map->off_map));
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data data;
	g_var = 0;
	char *map = ft_strjoin("map/", av[1]);
	map = ft_strjoin(map, ".cub");
	ft_parse(map, &data);
	data.map->off_map = 20;
	for (int i = 0; i < data.map->ymap; i++)
	{
		for (int j = 0; j < data.map->xmap; j++)
			printf("%d", data.map->map_compo[i * data.map->xmap + j]);
		printf("\n");
	}
	ft_init(&data);
	ft_draw_init(&data);
	// ft_coordinante(&data);
	mlx_hook(data.win, 2, 1L<<0, ft_key, &data);
	mlx_loop(data.mlx);
}
