/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:10 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/10 02:46:14 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_img(t_data *data)
{
	t_img *img = data->img;

	img->img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line, &img->endian);
}

void	ft_player_init(t_data *data)
{
	t_player	*player;
	t_map		*map;

	player = data->player;
	map = data->map;
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < map->ymap)
	{
		j = 0;
		while (j < map->xmap)
		{
			if (map->map_compo[i * map->xmap + j] == 8)
				break;
			j++;
		}
		if (map->map_compo[i * map->xmap + j] == 8)
			break;
		i++;
	}
	printf("%d\n", i);
	player->height = 5;
	player->width = 5;
	player->xpos = j * map->off_map + map->off_map / 2;
	player->ypos = i * map->off_map + map->off_map / 2;
	player->point->x = player->xpos;
	player->point->y = player->ypos;
	player->angle = 30 * 0.0174533;
	player->xrot = cos(player->angle);
	player->yrot = sin(player->angle);
}

void	ft_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx,WIDTH, HEIGHT, "ZEB!");
	ft_init_img(data);
	ft_player_init(data);
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

	b = data->ray->hit_point_v;
	player = data->player;
	ray = data->ray;
	if (((ray->angle < 2*PI) && (ray->angle > 3 * PI / 2)) \
			|| ((ray->angle > 0) && (ray->angle < PI / 2)))
	{
		b->x = (int)(player->xpos / data->map->off_map) * data->map->off_map + data->map->off_map + 0.00001;
		b->y = player->ypos - ((player->xpos - b->x) * tan(ray->angle));
	}
	if (((ray->angle <  3 * PI / 2) && (ray->angle > PI)) \
			|| ((ray->angle < PI) && (ray->angle > PI / 2)))
	{
		b->x = (int)(player->xpos / data->map->off_map) * data->map->off_map - 0.00001 ;
		b->y = player->ypos - ((player->xpos - b->x) * tan(ray->angle));
	}
	// if ((int)(ray->angle * RAD_TO_DEG) == 90 || (int)(ray->angle * RAD_TO_DEG) == 180 + 90)
	// {
	// 	b->x = player->point->x;
	// 	b->y = player->point->y;
	// }
}

t_vertex	*ft_horizontal_check(t_data *data)
{
	t_player	*player;
	t_ray		*ray;
	t_vertex	*b;

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
		b->y = (int)(player->ypos / data->map->off_map) * data->map->off_map + data->map->off_map + 0.00001;
		b->x = player->xpos - (player->ypos - b->y) / tan(ray->angle);
	}
	// if (ray->angle == PI || ray->angle == 0)
	// if ((int)(ray->angle * RAD_TO_DEG) == 360 || (int)(ray->angle * RAD_TO_DEG) == 180)
	// {
	// 	b->x = player->point->x;
	// 	b->y = player->point->y;
	// }
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

	rep = 0;
	printf("here1\n");
	if (((ray->angle < 2*PI) && (ray->angle > 3 * PI / 2)) \
			|| ((ray->angle > 0) && (ray->angle < PI / 2)))
	{
		xo = data->map->off_map;
		yo = xo * tan(ray->angle);
	}
	printf("here2\n");
	if (((ray->angle <  3 * PI / 2) && (ray->angle > PI)) \
			|| ((ray->angle < PI) && (ray->angle > PI / 2)))
	{
		xo = -data->map->off_map;
		yo = xo * tan(ray->angle);
	}
	printf("here3\n");
	if ((int)(ray->angle * RAD_TO_DEG) == 90 || (int)(ray->angle * RAD_TO_DEG) == (180 + 90) || data->ray->hit_point_v->y < 0 \
				|| (int)(data->ray->hit_point_v->y) > data->map->ymap * data->map->off_map)
		rep = data->map->ymap;
	printf("here4\n");
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

static void	ft_angle_adjust(t_data *data, float angle)
{
	t_ray	*ray;
	t_player	*player;

	ray = data->ray;
	player = data->player;
	ray->angle = player->angle - (angle * DEG_TO_RAD);
	if (ray->angle > 2 * PI)
		ray->angle -= 2 * PI;
	if (ray->angle < 0)
		ray->angle += 2 * PI;
}

void	ft_draw_line_mid(t_data *data, t_vertex *ray, float dist, float angle)
{
	float lineheight = (500 / dist);
	t_vertex *point1, *point2;

	point1 = malloc(sizeof(t_vertex));
	point2 = malloc(sizeof(t_vertex));

	point1->x = (WIDTH / 2) + (angle * (WIDTH / 120));
	point1->y = (HEIGHT / 2) - (lineheight / 2);
	if (point1->y <= 0)
		point1->y = 0;
	point2->x = (WIDTH / 2) + (angle * (WIDTH / 120));
	point2->y =  (HEIGHT / 2)  + (lineheight / 2);
	if (point2->y >= HEIGHT)
		point2->y = HEIGHT;
	// printf("height : %f\n", point1->y);
	// printf("height : %f\n", point2->y);
	// printf("w : %f\n", point1->x);
	// printf("w : %f\n", point2->x);
	//line x = 0, line y = Height / 2  - dist /2;
	// line x = 0, line y = HEGIHT / 2 + dist /2;
	// ft_vect_draw(point1, point2, 0xFF0000, data);
}

void	ft_draw_ray(t_data *data)
{
	t_vertex	horizontal;
	t_vertex	vertical;
	t_vertex	*nearest;
	t_ray*	ray;
	t_player	*player;
	float	h, v, dist;
	float	angle, min_angle, max_angle;

	ray = data->ray;
	player = data->player;
	min_angle = -60;
	max_angle = 60;
	while (min_angle < max_angle)
	{
		ft_angle_adjust(data, min_angle);
		ft_horizontal_check(data);
		ft_expand_hori(data);
		ft_vertical_check(data);
		ft_expand_verti(data);
		h = ft_hypo_calc(data->player->point, data->ray->hit_point_h)[0];
		v = ft_hypo_calc(data->player->point, data->ray->hit_point_v)[0];
		if (v < h)
		{
			dist = v;
			nearest = data->ray->hit_point_v;
		}
		else
		{
			dist = h;
			nearest = data->ray->hit_point_h;
		}
		if (dist)
			ft_draw_line_mid(data , nearest, dist , min_angle);
		ft_vect_draw(data->player->point, nearest, 0x00FF00, data);
		min_angle+=0.1;
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
