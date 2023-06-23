/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:20 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/23 19:43:48 by msamhaou         ###   ########.fr       */
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

void	ft_sigle_vect(double x, double y, t_data *data)
{
	t_vertex a, b;
	b.x = data->rect->xpos; b.y = data->rect->ypos;
	a.x = x; a.y = y;
	ft_vect_draw(&a, &b, data);
}

void	ft_coordinante(t_data *data)
{
	int i = 0;
	while (i < 8)
	{
		mlx_string_put(data->mlx, data->win, 64 * 8, 64 * i, 0x00FF00 ,ft_itoa(i * 64));
		i++;
	}
	i = 0;
	while (i < 8)
	{
		mlx_string_put(data->mlx, data->win, 64 * i, 64 * 8, 0x00FF00 ,ft_itoa(i * 64));
		i++;
	}
}

void	ft_vector_checker_test(t_data *data)
{
	static int i;
	double	hypo = 0;
	double	near_x = 0;
	double yy;

	near_x = ceil(data->rect->xpos/64) * 64;
	if ((data->rect->deg >  PI/2 && data->rect->deg < PI + PI/2) )
		near_x = floor(data->rect->xpos/64) * 64;
	hypo = (near_x - data->rect->xpos) / cos (data->rect->deg);
	yy = data->rect->ypos + sin(data->rect->deg) * hypo;
	if (yy < 0 || yy > HEIGHT)
		hypo = 600;
	yy = data->rect->ypos + sin(data->rect->deg) * hypo;
	ft_sigle_vect(near_x, data->rect->ypos,data);
	ft_sigle_vect(data->rect->xpos, yy,data);
	ft_sigle_vect(data->rect->xpos + cos(data->rect->deg) * hypo , yy,data);
}

void	ft_motion(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	ft_map(data);
	ft_draw_character(data);
	ft_rot(data);

	/**/
	ft_vector_checker_test(data);
	ft_put_img(data);

	ft_coordinante(data);
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
