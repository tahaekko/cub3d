/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:20 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/21 22:56:06 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_hypo(t_data *data)
{
	int hypo = 100;
	t_rect	*rect = data->rect;

	// for (int i = 0; i < hypo; i++)
		// ft_put_pix(rect->rotx, rect->roty, 0x00FF00, data);
}

void	ft_rot(t_data *data)
{
	t_rect *rect;
	int i = 0;

	rect = data->rect;
	if (rect->deg > 2 * PI)
		rect->deg -= 2 * PI;
	if (rect->deg < 0)
		rect->deg += 2 * PI;
	rect->rotx = cos(rect->deg);
	rect->roty = sin(rect->deg);
	while (i < rect->ray_len)
	{
		ft_put_pix(rect->xpos + (i * rect->rotx), rect->ypos + (i * rect->roty), RAY, data);
		i++;
	}
}

void	ft_motion(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	ft_map(data);
	ft_draw_character(data);
	ft_rot(data);

	/**/
	t_vertex a, b;
	a.x = 100; a.y = 100;
	b.x = 500; b.y = 500;

	ft_vect_draw(&a, &b, data);

	ft_put_pix(a.x, a.y, 0x0000FF, data);
	ft_put_pix(b.x, b.y, 0x0000FF, data);

	ft_put_img(data);
}

void	ft_move(t_data *data, int key)
{
	if (key == KEY_UP)
		data->rect->ray_len +=5;
	if (key == KEY_DN)
		data->rect->ray_len -= 5;
	if (key == KEY_RG)
		data->rect->deg+= 0.1;
	if (key == KEY_LE)
		data->rect->deg-=0.1;
	if (key == KEY_S)
	{
		data->rect->xpos-= data->rect->rotx;
		data->rect->ypos -= data->rect->roty;
	}
	if (key == KEY_W)
	{
		data->rect->xpos+= data->rect->rotx;
		data->rect->ypos+= data->rect->roty;
	}
	if (key == KEY_D)
		data->rect->xpos += data->rect->rotx;
	if (key == KEY_A)
		data->rect->xpos -= data->rect->rotx;;
	if (key == ESC)
		exit(0);
	printf("X %f\n", data->rect->xpos);
	printf("C: %f , F : %f", ceil(data->rect->xpos / 64) * 64, floor(data->rect->xpos / 64));


	printf("Y %f\n", data->rect->ypos/ 64);
	ft_motion(data);
}

int	ft_key(int key, t_data *data)
{
	ft_move(data, key);
	return (0);
}

void	ft_map(t_data *data)
{
	int	xmap, ymap, off_map;

	xmap = 8;
	ymap = 8;
	off_map = 64;
	int map[] =	{1,1,1,1,1,1,1,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,1,0,0,0,1,
				 1,0,0,1,0,0,0,1,
				 1,1,1,1,1,1,1,1};
	int color, i, j;
	color = 0;
	i = 0;
	j = 0;

	while (i < xmap)
	{
		j = 0;
		while (j < ymap)
		{
			// printf("%d, ", map[(j * ymap) + i]);
			if (map[(j * ymap) + i] == 1)
				color = WALL;
			else
				color = FLOOR;
			ft_draw_square(data, i *  off_map , j *  off_map, color, off_map);
			j++;
		}
		i++;
		// printf("\n");
	}
}

int	main()
{
	t_data data;

	ft_init(&data);
	data.rect = ft_rect_init();
	ft_map(&data);
	ft_draw_character(&data);
	ft_put_img(&data);
	mlx_hook(data.win, 2, 1L<<0, ft_key, &data);
	mlx_loop(data.mlx);
}
