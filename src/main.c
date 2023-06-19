#include "cub3d.h"

void	ft_draw_hypo(t_data *data)
{
	int hypo = 100;
	t_rect	*rect = data->rect;

	// for (int i = 0; i < hypo; i++)
		// ft_put_pix(rect->rotx, rect->roty, 0x00FF00, data);
}

void	ft_rot(t_rect *rect)
{
	int	hypo = 100;
	int	x;
	int	y;
	if (rect->deg > 360)
		rect->deg = 0;
	if (rect->deg < 0)
		rect->deg = 360;
	rect->rotx = cos(rect->deg) * hypo;
	rect->roty = sin(rect->deg) * hypo;
}

void	ft_motion(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	ft_map(data);
	ft_draw_character(data);
	// ft_draw_hypo(data);
	ft_put_img(data);
}

void	ft_move(t_data *data, int key)
{
	if (key == KEY_S)
		data->rect->ypos++;
	if (key == KEY_W)
		data->rect->ypos--;
	if (key == KEY_D)
		data->rect->xpos++;
	if (key == KEY_A)
		data->rect->xpos--;
	if (key == KEY_RG)
		data->rect->deg++;
	if (key == KEY_LE)
		data->rect->deg--;
	if (key == ESC)
		exit(0);
	ft_rot(data->rect);
	printf("%d\n", data->rect->deg);
	ft_motion(data);
}

int	ft_key(int key, t_data *data)
{
	printf("%d\n", key);
	ft_move(data, key);
	return (0);
}

void	ft_map(t_data *data)
{
	int	xmap, ymap, off_map;

	xmap = 8;
	ymap = 8;
	off_map = WIDTH/8;
	int map[] =	{1,1,1,1,1,1,1,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
				 1,0,0,0,0,0,0,1,
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
				color = 0xFF0000;
			else
				color = 0x0000FF;
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
