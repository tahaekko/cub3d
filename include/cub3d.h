/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taha <taha@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:54:38 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/19 11:02:36 by taha             ###   ########.fr       */
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
# define WIDTH 660
# define HEIGHT 660
# define FOV 60
# define PI 3.141592653589793
# define RAD_TO_DEG 57.2958
# define DEG_TO_RAD 0.0174533
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

typedef struct s_color
{
	int	floor;
	int	ciel;
}	t_color;

typedef struct s_file
{
	char	*north;
	char	*west;
	char	*east;
	char	*south;
}	t_file;
typedef struct s_vertex
{
	double	x;
	double	y;
}	t_vertex;

typedef struct s_vect
{
	t_vertex	a;
	t_vertex	b;
}	t_vect;

typedef struct s_player
{
	int		height;
	int		width;
	double	xpos;
	t_vertex	point[1];
	double	ypos;
	double	angle;
	double	xrot;
	double	yrot;
}	t_player;

typedef struct s_img{
	void	*img_ptr;
	char	*addr;
	int		line;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_texture
{
	int		w;
	int		h;
	t_img	*texture_img;
}	t_texture;

typedef struct s_map
{
	int	xmap;
	int	ymap;
	int off_map;
	int	*map_compo;
}	t_map;

typedef	struct s_ray
{
	t_vertex	hit_point_h[1];
	t_vertex	hit_point_v[1];
	double		angle;
}	t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img[1];
	t_map		map[1];
	t_player	player[1];
	t_ray		ray[1];
	t_file			file[1];
	t_color			colors[1];
	t_texture		**texture;
	char			**files_arr;
}	t_data;


void	ft_init(t_data *data);
void	ft_put_pix(int x, int y, int color, t_data *data);
void	ft_put_img(t_data *data);
void	ft_draw_square(t_data *data, int xpos, int ypos, int color, int size);
void	ft_background(t_data *data);
void	ft_draw_map(t_data *data);
void	ft_draw_init(t_data *data);
void	ft_parse(char *filename, t_data *data);
void	ft_vect_draw(t_vertex *a, t_vertex *b, int color, t_data *data);
void	ft_coordinante(t_data *data);
double	*ft_hypo_calc(t_vertex *a, t_vertex *b);
int	color_code(int r ,int g ,int b);

#endif
