/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:54:11 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/26 18:57:38 by msamhaou         ###   ########.fr       */
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

int	main()
{
	t_data data;
	ft_parse("map/map.cub");
	// ft_init(&data);
	// ft_draw_init(&data);
	// ft_put_img(&data);
	// mlx_hook(data.win, 2, 1L<<0, ft_key, &data);
	// mlx_loop(data.mlx);
}
