/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:10 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/07 19:39:29 by msamhaou         ###   ########.fr       */
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
	t_ray		*ray;
	t_vertex	*b;
	float	new_angle;

	b = data->ray->hit_point_v;
	player = data->player;
	ray = data->ray;
	if (((ray->angle < 2*PI) && (ray->angle > 3 * PI / 2)) \
			|| ((ray->angle > 0) && (ray->angle < PI / 2)))
	{
		b->x = (int)(player->xpos / data->map->off_map) * data->map->off_map + data->map->off_map - 0.00001;
		b->y = player->ypos - ((player->xpos - b->x) * tan(ray->angle));
	}
	if (((ray->angle <  3 * PI / 2) && (ray->angle > PI)) \
			|| ((ray->angle < PI) && (ray->angle > PI / 2)))
	{
		b->x = (int)(player->xpos / data->map->off_map) * data->map->off_map - 0.00001 ;
		b->y = player->ypos - ((player->xpos - b->x) * tan(ray->angle));
	}
	if ((int)(ray->angle * RAD_TO_DEG) == 90 || (int)(ray->angle * RAD_TO_DEG) == 180 + 90)
	{
		b->x = player->point->x;
		b->y = player->point->y;
	}
}

t_vertex	*ft_horizontal_check(t_data *data)
{
	t_player	*player;
	t_ray		*ray;
	t_vertex	*b;
	float	new_angle;

	player = data->player;
	ray = data->ray;
	b = data->ray->hit_point_h;
	if (ray->angle > PI)
	{
		b->y = (int)(player->ypos / data->map->off_map) * data->map->off_map - 0.00001;
		b->x = player->xpos - (player->ypos - b->y) / tan(ray->angle);
	}
	if (ray->angle < PI)
	{
		b->y = (int)(player->ypos / data->map->off_map) * data->map->off_map + data->map->off_map - 0.00001;
		b->x = player->xpos - (player->ypos - b->y) / tan(ray->angle);
	}
	// if (ray->angle == PI || ray->angle == 0)
	if ((int)(ray->angle * RAD_TO_DEG) == 360 || (int)(ray->angle * RAD_TO_DEG) == 180)
	{
		b->x = player->point->x;
		b->y = player->point->y;
	}
	return (b);
}

void	ft_expand_hori(t_data *data)
{
	t_player *player;
	t_ray	*ray;
	int	rep = 0;
	int	x;
	int	y;
	float	xo;
	float	yo;

	player = data->player;
	ray = data->ray;
	if(ray->angle > PI)
	{
		yo = -data->map->off_map;
		xo = yo / tan(ray->angle);
	}
	if(ray->angle < PI)
	{
		yo = data->map->off_map;
		xo = yo / tan(ray->angle);
	}
	if ((int)(ray->angle * RAD_TO_DEG) == 360 || (int)(ray->angle * RAD_TO_DEG) == 180 || data->ray->hit_point_h->x < 0 \
				|| data->ray->hit_point_h->x > data->map->xmap * data->map->off_map)
		rep = data->map->ymap;
	while (rep < data->map->ymap)
	{
		x = (int)(data->ray->hit_point_h->x / data->map->off_map);
		y = (int)(data->ray->hit_point_h->y / data->map->off_map);
		if (data->map->map_compo[y * data->map->xmap + x] == 1)
			break;
		data->ray->hit_point_h->x += xo;
		data->ray->hit_point_h->y += yo;
		rep++;
	}
}

void	ft_expand_verti(t_data *data)
{
	t_ray	*ray = data->ray;
	t_player	*player = data->player;
	int	x;
	int	y;
	int rep;
	float	xo, yo;
	float	new_angle;

	new_angle = player->angle - (30 * DEG_TO_RAD);
	rep = 0;
	if (((new_angle < 2*PI) && (new_angle > 3 * PI / 2)) \
			|| ((new_angle > 0) && (new_angle < PI / 2)))
	{
		xo = data->map->off_map;
		yo = xo * tan(new_angle);
	}
	if (((new_angle <  3 * PI / 2) && (new_angle > PI)) \
			|| ((new_angle < PI) && (new_angle > PI / 2)))
	{
		xo = -data->map->off_map;
		yo = xo * tan(new_angle);
	}
	if ((int)(new_angle * RAD_TO_DEG) == 90 || (int)(new_angle * RAD_TO_DEG) == (180 + 90) || data->ray->hit_point_v->y < 0 \
				|| (int)(data->ray->hit_point_v->y) > data->map->ymap * data->map->off_map)
		rep = data->map->ymap;
	while (rep < data->map->ymap)
	{
		x = (int)(data->ray->hit_point_v->x / data->map->off_map);
		y = (int)(data->ray->hit_point_v->y / data->map->off_map);
		if (data->map->map_compo[y * data->map->xmap + x] == 1)
			break;
		data->ray->hit_point_v->x += xo;
		data->ray->hit_point_v->y += yo;
		rep++;
	}
}

void	ft_draw_ray(t_data *data)
{
	static t_vertex	horizontal;
	t_vertex	vertical;
	t_vertex		to_draw;
	float	h, v;
	int	angle, min_angle, max_angle;
	t_ray*	ray;
	t_player	*player;
	ray = data->ray;
	player = data->player;

	min_angle = -60;
	min_angle = 60;
	while (min_angle)
	{
		ray->angle = player->angle - (min_angle * DEG_TO_RAD);
		ft_horizontal_check(data);
		ft_expand_hori(data);
		ft_vertical_check(data);
		ft_expand_verti(data);
		h = ft_hypo_calc(data->player->point, data->ray->hit_point_h)[0];
		v = ft_hypo_calc(data->player->point, data->ray->hit_point_v)[0];
		if (v < h)
			ft_vect_draw(data->player->point, data->ray->hit_point_v, 0xFF0000, data);
		else
			ft_vect_draw(data->player->point, data->ray->hit_point_h, 0x00FF00, data);
		min_angle++;
	}
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
