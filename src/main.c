/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:54:11 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/28 03:20:53 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int	ft_key(int key)
{
	printf("%d\n", key);
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
	// ft_init(&data);
	// ft_draw_init(&data);
	// ft_put_img(&data);
	// mlx_hook(data.win, 2, 1L<<0, ft_key, &data);
	// mlx_loop(data.mlx);
}
