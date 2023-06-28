/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:54:38 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/28 03:19:15 by taha             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# define WIDTH 1080
# define HEIGHT 720
# define PI 3.141592653589793
# define GRID 64

#define RECTCOLOR 0x7BB30C
#define FLOOR 0x1859B3
#define WALL 0x2DB362
#define RAY 0xB3160C
#define GRID_C 0x9029B3

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

typedef struct s_vertex
{
	float	x;
	float	y;
}	t_vertex;

typedef struct s_vect
{
	t_vertex	a;
	t_vertex	b;
}	t_vect;

typedef struct s_player
{
	float	xpos;
	float	ypos;
	float	angle;
	float	xrot;
	float	yrot;
}	t_player;

typedef struct s_img{
	void	*img_ptr;
	char	*addr;
	int		line;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_map
{
	int	xmap;
	int	ymap;
	int	*map_compo;
}	t_map;


typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img[1];
	t_map		map[1];
	t_player	player[1];
}	t_data;


void	ft_init(t_data *data);
void	ft_put_pix(int x, int y, int color, t_data *data);
void	ft_put_img(t_data *data);
void	ft_draw_square(t_data *data, int xpos, int ypos, int color, int size);
void	ft_background(t_data *data);
void	ft_draw_map(t_data *data);
void	ft_draw_init(t_data *data);
void	ft_parse(char *filename, t_data *data);

#endif
