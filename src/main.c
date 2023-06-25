/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:20 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/25 15:05:03 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	int xmap = 8;
	int ymap = 8;
	int off_map = 64;
	int map[] =	{1,1,1,1,1,1,1,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,1,0,0,0,1,
				 1,0,0,1,0,0,0,1,
				 1,1,1,1,1,1,1,1};

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

void	ft_sigle_vect(float x, float y, int color,t_data *data)
{
	t_vertex a, b;
	b.x = data->rect->xpos; b.y = data->rect->ypos;
	a.x = x; a.y = y;
	ft_vect_draw(&a, &b, color,data);
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

int	*ft_conv_to_map(float x, float y)
{
	int	mpx, mpy;
	int cordinnates;
	int *ret = malloc(sizeof(int) * 2);

	ret[0] = ((int)(x / 64)*64) / 64;
	ret[1] = ((int)(y / 64)*64) / 64;
	printf("x %d\n", ret[0]);
	printf("y %d\n", ret[1]);
	return (ret);
}

t_vertex	ft_vector_vertical_test(t_data *data)
{
	int rep ,xo, yo;
	t_vertex ret;
	rep = 0;
	float	near_x = 0;
	float yy , newx , newy;
	int	color = 0x00FF00;

 // [2PI, 3PI/2] && [0 , PI/2]
	if (((data->rect->deg < 2*PI) && (data->rect->deg > 3 * PI / 2)) \
			|| ((data->rect->deg > 0) && (data->rect->deg < PI / 2)))
	{
		near_x = (int)(data->rect->xpos / 64) * 64 + 64;
		yy = data->rect->ypos - (tan(data->rect->deg) * (data->rect->xpos - near_x));
		xo = 64;
		yo = xo * tan(data->rect->deg);
		newx = near_x + xo;
		newy = yy + yo;
	}
	if (((data->rect->deg <  3 * PI / 2) && (data->rect->deg > PI)) \
			|| ((data->rect->deg < PI) && (data->rect->deg > PI / 2)))
	{
		near_x = ((int)(data->rect->xpos/64) * 64) - 0.0001;
		yy = data->rect->ypos - (tan(data->rect->deg) * (data->rect->xpos - near_x));
		xo = -64;
		yo = xo * tan(data->rect->deg);
		newx = near_x + xo;
		newy = yy + yo;
	}
	if ((data->rect->deg == PI / 2) || (data->rect->deg == 3 * (PI / 2)))
	{
		near_x = data->rect->xpos;
		yy = data->rect->ypos;
		rep = 8;
	}
	printf("yy %f\n", yy);
	ft_sigle_vect(near_x , data->rect->ypos, 0x0000FF, data);
	int	*iswall;
	int	mp;
	while (rep < 8)
	{
		iswall = ft_conv_to_map(near_x, yy);
		mp = xmap * iswall[1] + iswall[0];
		printf("1 mp %d\n", mp);
		if ( mp < xmap * ymap && map[mp] == 1)
			break;
		else
		{
			near_x += xo;
			yy += yo;
			rep++;
		}
	}
	ret.x = near_x; ret.y = yy;
	return (ret);
}



t_vertex	ft_vector_horizontal_test(t_data *data)
{
	int rep, xo, yo;
	rep = 0;
	t_vertex	ret;
	float	near_y = 0;
	float xx ,newx, newy;
	int	color = 0x0000FF;

	if (data->rect->deg < PI)
	{
		near_y = (int)(data->rect->ypos/64) * 64 + 64;
		xx = data->rect->xpos - (data->rect->ypos - near_y) / tan(data->rect->deg);
		yo = 64;
		xo = yo /tan(data->rect->deg);
		newx = xx + xo;
		newy = near_y + yo;
	}
	if (data->rect->deg > PI)
	{
		near_y = ((int)(data->rect->ypos/64) * 64) - 0.00001;
		xx = data->rect->xpos - (data->rect->ypos - near_y) / tan(data->rect->deg);
		yo = -64;
		xo = yo /tan(data->rect->deg);
		newx = xx + xo;
		newy = near_y + yo;
	}
	if (data->rect->deg == 0 || data->rect->deg == PI)
	{
		xx = data->rect->xpos;
		near_y = data->rect->ypos;
		rep = 8;
	}
	int	*iswall;
	int	mp;
	while (rep < 8)
	{
		iswall = ft_conv_to_map(xx, near_y);
		mp = xmap * iswall[1] + iswall[0];
		printf("2 mp %d\n", mp);
		if ( mp < xmap * ymap && map[mp] == 1)
			break;
		else
		{
			xx += xo;
			near_y += yo;
			rep++;
		}
	}
	ret.x = xx; ret.y = near_y;
	return (ret);
}

float	dist(t_vertex player, t_vertex point)
{
	return (sqrt(((point.x - player.x) * (point.x - player.x)) + ((point.y - player.y) * (point.y - player.y))));
}

void	ft_motion(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	ft_map(data);
	ft_draw_character(data);
	ft_rot(data);

	/**/
	t_vertex hori = ft_vector_horizontal_test(data);
	t_vertex verti =ft_vector_vertical_test(data);
	t_vertex player;
	player.x = data->rect->xpos;
	player.y = data->rect->ypos;

	float d1 , d2;
	d1 = dist(player, hori);
	d2 = dist(player, verti);
	if (d1 < d2)
		ft_vect_draw(&player, &hori, 0x00FF00, data);
	else
		ft_vect_draw(&player, &verti, 0xFF0000, data);
	ft_put_img(data);

	ft_coordinante(data);
}

void	ft_move(t_data *data, int key)
{
	float speed;

	speed = 5;
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
		data->rect->xpos-= data->rect->rotx * speed;
		data->rect->ypos -= data->rect->roty * speed;
	}
	if (key == KEY_W)
	{
		data->rect->xpos+= data->rect->rotx * speed;
		data->rect->ypos+= data->rect->roty * speed;
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
