/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:10 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/04 17:52:23 by taha             ###   ########.fr       */
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
	player->xpos = 70;
	player->ypos = 70;
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
		ft_put_pix(player->xpos + i * player->xrot, player->ypos + i * player->yrot, 0xFF0000, data);
		i++;
	}
}

void	ft_vertical_check(t_data *data)
{
	t_player	*player;
	t_vertex	*b;

	b = data->ray->hit_point;
	player = data->player;
	if (((player->angle < 2*PI) && (player->angle > 3 * PI / 2)) \
			|| ((player->angle > 0) && (player->angle < PI / 2)))
	{
		b->x = (int)(player->xpos / data->map->off_map) * data->map->off_map + data->map->off_map - 0.00001;
		b->y = player->ypos - ((player->xpos - b->x) * tan(player->angle));
	}
	if (((player->angle <  3 * PI / 2) && (player->angle > PI)) \
			|| ((player->angle < PI) && (player->angle > PI / 2)))
	{
		b->x = (int)(player->xpos / data->map->off_map) * data->map->off_map - 0.00001 ;
		b->y = player->ypos - ((player->xpos - b->x) * tan(player->angle));
	}
	if (player->angle == 3 * (PI / 2) || player->angle == PI/2)
	{
		b->x = player->point->x;
		b->y = player->point->y;
	}
}

t_vertex	*ft_horizontal_check(t_data *data)
{
	t_player	*player;
	t_vertex	*b;

	player = data->player;
	b = data->ray->hit_point;
	printf("%f rad == %f deg \n", player->angle, player->angle * 57.2958);
	if (player->angle > PI)
	{
		printf("Down\n");
		b->y = (int)(player->ypos / data->map->off_map) * data->map->off_map - 0.00001;
		b->x = player->xpos - (player->ypos - b->y) / tan(player->angle);
	}
	if (player->angle < PI)
	{
		printf("UP\n");
		b->y = (int)(player->ypos / data->map->off_map) * data->map->off_map + data->map->off_map - 0.00001;
		b->x = player->xpos - (player->ypos - b->y) / tan(player->angle);
	}
	if (player->angle == PI || player->angle == 0)
	{
		b->x = player->point->x;
		b->y = player->point->y;
	}
	return (b);
}

void	ft_expand_hori(t_data *data)
{
	t_vertex *hori;
	t_player *player;
	int	rep = 0;
	int	mp, x, y;
	float	xo, yo , prevx, prevy;


	player = data->player;
	if(player->angle > PI)
	{
		yo = -data->map->off_map;
		xo = yo / tan(data->player->angle);
	}
	if(player->angle < PI)
	{
		yo = data->map->off_map;
		xo = yo / tan(data->player->angle);
	}
	if (player->angle == PI || player->angle == 0 || data->ray->hit_point->x < 0 || data->ray->hit_point->x > data->map->xmap * data->map->off_map)
		rep == data->map->ymap;
	while (rep < data->map->ymap)
	{
		data->ray->hit_point->x += xo;
		data->ray->hit_point->y += yo;
		x = (int)(data->ray->hit_point->x / data->map->off_map);
		y = (int)(data->ray->hit_point->y / data->map->off_map);
		if (data->map->map_compo[y * data->map->xmap + x] == 1)
			break;
		rep++;
	}
}

void	ft_draw_ray(t_data *data)
{
	static t_vertex	horizontal;
	t_vertex	vertical;
	t_vertex		to_draw;

	ft_horizontal_check(data);
	ft_expand_hori(data);
	// vertical = ft_veriacal_check(data);

	ft_vect_draw(data->player->point, data->ray->hit_point, 0x00FF00, data);
}

void	ft_draw_init(t_data *data)
{
	t_player	*player;

	player = data->player;
	// ft_coordinante(data);
	ft_background(data);
	ft_draw_map(data);
	ft_draw_square(data, player->xpos, player->ypos, 0x0ef0e5, player->height);
	ft_draw_direction(data);
	ft_draw_ray(data);
	ft_put_img(data);
}
