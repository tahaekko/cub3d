/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:10 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/22 18:57:16 by taha             ###   ########.fr       */
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
	player->angle = (double)((int)(FOV/ 2)) * (double)0.0174533;
	player->xrot = cos(player->angle);
	player->yrot = sin(player->angle);
}

t_texture	**ft_textures_alloc(t_data *data)
{
	t_texture	**textures;
	int			i;

	textures = malloc(sizeof(t_texture *) * (5));
	i=0;
	while (data->files_arr[i])
	{
		textures[i] = malloc(sizeof(t_texture));
		textures[i++]->texture_img = malloc(sizeof(t_img));
	}
	textures[i] = NULL;
	return (textures);
}

void	ft_set_texture_img(t_data *data, t_texture *texture, char *file_name, int i)
{
	void	*pointer;
	t_img	*img;

	pointer = mlx_xpm_file_to_image(data->mlx, file_name, &texture->w, &texture->h);
	img = texture->texture_img;
	texture->texture_img->addr = mlx_get_data_addr(pointer, &img->bpp, &img->line, &img->endian);
	free(pointer);
}

void	ft_texture_set(t_texture **textures, t_data *data)
{
	int	i;

	i = 0;
	while (textures[i])
	{
		ft_set_texture_img(data, textures[i], data->files_arr[i], i);
		i++;
	}
}
void	ft_texture_init(t_data *data)
{
	t_texture	**textures;
	t_elem		*elem;

	textures = ft_textures_alloc(data);
	ft_texture_set(textures, data);
	data->texture = textures;
	elem = ft_single_color((int *)data->texture[1]->texture_img->addr);
	for(; elem;elem=elem->next)
		printf("%X\n", elem->content);
}

void	ft_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx,WIDTH, HEIGHT, "ZEB!");
	ft_init_img(data);
	ft_player_init(data);
	ft_texture_init(data);
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
	return (b);
}

void	ft_expand_hori(t_data *data)
{
	t_player *player;
	t_ray	*ray;
	int	rep = 0;
	int	x;
	int	y;
	double	xo;
	double	yo;

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
	double	xo, yo;

	rep = 0;
	xo = 0;
	yo = 0;
	if (((ray->angle < 2*PI) && (ray->angle > 3 * PI / 2)) \
			|| ((ray->angle > 0) && (ray->angle < PI / 2)))
	{
		xo = (double) data->map->off_map;
		yo = xo * tan(ray->angle);
	}
	if (((ray->angle <  3 * PI / 2) && (ray->angle > PI)) \
			|| ((ray->angle < PI) && (ray->angle > PI / 2)))
	{
		xo = (double)(-data->map->off_map);
		yo = xo * tan(ray->angle);
	}
	if ((int)(ray->angle * RAD_TO_DEG) == 90 || (int)(ray->angle * RAD_TO_DEG) == (180 + 90) || data->ray->hit_point_v->y < 0 \
				|| (int)(data->ray->hit_point_v->y) > data->map->ymap * data->map->off_map)
		rep = data->map->ymap;
	while (rep < data->map->xmap)
	{
		x = (int)(data->ray->hit_point_v->x /(double)data->map->off_map);
		y = (int)(data->ray->hit_point_v->y / (double)data->map->off_map);
		if ((y * data->map->xmap + x > data->map->xmap * data->map->ymap) || (y * data->map->xmap + x < 0))
			return ;
		if (data->map->map_compo[y * data->map->xmap + x] == 1)
			break;
		data->ray->hit_point_v->x += xo;
		data->ray->hit_point_v->y += yo;
		rep++;
	}
}

static void	ft_angle_adjust(double *angle)
{
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
	if (*angle < 0)
		*angle += 2 * PI;
}

void	ft_draw_line_mid(t_data *data, double dist, int nray, t_vertex *near,int color)
{
	double newray;
	t_player *player = data->player;
	t_ray	*ray = data->ray;

	newray = player->angle - ray->angle;
	ft_angle_adjust(&newray);
	double l_h = (double)HEIGHT / (double)(dist * cos(newray)) * 512;

	int	i = HEIGHT/ 2  - ((int)l_h / 2);
	int	height = 0;
	int	x,y,step;

	if (near == ray->hit_point_h)
		x = (((int)near->x % data->map->off_map) * (data->texture[0]->w)) / data->map->off_map;
	else
		x = (((int)near->y % data->map->off_map) * (data->texture[0]->w )) / data->map->off_map;
	step = 0;
	int	*addr = (int *)data->texture[0]->texture_img->addr;
	while (i < (HEIGHT/ 2  + ((int)l_h / 2)))
	{
		y = (step * data->texture[0]->w) / (int)l_h;
		ft_put_pix(nray, i, addr[(y * data->texture[0]->w )+ x],data);
		i++;
		step++;
	}
}

void	ft_debug(t_player *player, t_ray *ray, int nray, double dist, t_data *data)
{
	double newray, nnray;

	newray = player->angle - ray->angle;
		ft_angle_adjust(&newray);
		nnray = player->angle - newray;
		ft_angle_adjust(&nnray);
		printf("nray : %d\n", nray);
		printf("dist : %f\n", dist);
		if (nray != 30)
		{
			double maxdeg = ((double)FOV * (double)DEG_TO_RAD);
			ft_angle_adjust(&maxdeg);
			double newnew = data->ray->angle / maxdeg;
			ft_angle_adjust(&newnew);
			printf("x to draw %f\n", (double)nray / (double)FOV * ((double)(WIDTH)));
			printf("dist of other %f \n", dist * cos(nnray));
		}

		printf("\n");
		printf("player angle In Rad : %f\n", player->angle);
		printf("ray angle In Rad :%f\n", ray->angle);
		printf("Diff Rad befor addjust %f\n", player->angle - ray->angle);
		printf("Diff Rad after addjust %f\n", newray);
		printf("that might be the real Diff Rad after addjust %f\n", nnray);
		printf("\n");
		printf("player angle In Deg : %f\n", player->angle * RAD_TO_DEG);
		printf("ray angle In Deg :%f\n", ray->angle * RAD_TO_DEG);
		printf("that might be the real Diff Deg after addjust %f\n", nnray * RAD_TO_DEG);
		printf("Diff Deg %f\n\n\n", newray *RAD_TO_DEG);
}

void	ft_draw_ray(t_data *data)
{
	t_vertex	*nearest;
	t_ray*	ray;
	t_player	*player;
	double	h, v, dist;
	int color;
	ray = data->ray;
	player = data->player;
	ray->angle = player->angle - ((double)((int)(FOV / 2))  * DEG_TO_RAD);
	ft_angle_adjust(&ray->angle);
	double	nray=-0.00001;
	int	nnray = 0;
	color = 0;
	while (nray < (double)FOV)
	{
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
			color = color_code(200,0,50);
		}
		else
		{
			dist = h;
			nearest = data->ray->hit_point_h;
			color = color_code(255, 0, 105);
		}
		if (dist)
			ft_draw_line_mid(data , dist, nnray, nearest, color);
		ray->angle += ((double)60/ (double)WIDTH) * (double)DEG_TO_RAD;
		ft_angle_adjust(&ray->angle);
		nray+= ((double)60/ (double)WIDTH);
		nnray++;
	}
}

void	ft_paint(t_data *data, int color)
{
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT/2; j++)
			ft_put_pix(i, j, color, data);
}
void	ft_paint_floor(t_data *data, int color)
{
	for (int i = 0; i < WIDTH; i++)
		for (int j = HEIGHT/2; j < HEIGHT; j++)
			ft_put_pix(i, j, color, data);
}

void	ft_draw_init(t_data *data)
{
	t_player	*player;

	player = data->player;
	ft_coordinante(data);
	// ft_background(data);
	ft_paint(data, data->colors->ciel);
	ft_paint_floor(data, data->colors->floor);
	// ft_draw_map(data);
	// ft_draw_square(data, player->xpos, player->ypos, 0x0ef0e5, player->height);
	// ft_draw_direction(data);
	ft_draw_ray(data);
	ft_put_img(data);
}
