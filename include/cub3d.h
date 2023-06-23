/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:24:45 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/22 16:56:37 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <libft.h>

#define HEIGHT 600
#define WIDTH 600
#define PI 3.141592653589793

#define RECTCOLOR 0x7BB30C
#define FLOOR 0x1859B3
#define WALL 0x2DB362
#define RAY 0xB3160C
#define GRID 0x9029B3

/*Key kode define*/


#ifdef __linux__
	#define KEY_UP 65362
	#define KEY_DN 65364
	#define KEY_RG 65363
	#define KEY_LE 65361
	#define KEY_W 119
	#define KEY_S 115
	#define KEY_D 100
	#define KEY_A 97
	#define ESC 65307
#else
	#define KEY_UP 126
	#define KEY_DN 125
	#define KEY_RG 124
	#define KEY_LE 123
	#define KEY_W 13
	#define KEY_S 1
	#define KEY_D 2
	#define KEY_A 0
	#define ESC 53

#endif

typedef struct s_test
{
	double	btw;
	double	hypo;
}	t_test;

typedef struct s_vertex
{
	double	x;
	double	y;
}	t_vertex;

typedef struct s_rect{
	double	xpos;
	double	ypos;
	double	deg;
	double	rotx;
	double	roty;
	double	ray_len;
	int	height;
	int	width;
	int	color;
}	t_rect;

typedef struct s_img{
	void	*img_ptr;
	char	*addr;
	int		line_len;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_data{
	void	*mlx;
	void	*win;
	t_img	*img;
	t_rect	*rect;
}	t_data;

void	ft_init_img(t_data *data);
void	ft_init(t_data *data);
void	ft_put_pix(int x, int y, int color,t_data *data);
void	ft_put_img(t_data *data);
t_rect	*ft_rect_init();
void	ft_draw_character(t_data *data);
void	ft_map(t_data *data);
void	ft_draw_square(t_data *data, int xpos, int ypos, int color, int size);
void	ft_background(t_data *data);

/**/
double	*ft_hypo_calc(t_vertex *a, t_vertex *b);
void	ft_vect_draw(t_vertex *a, t_vertex *b, t_data *data);

