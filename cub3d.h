#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HEIGHT 600
#define WIDTH 600

typedef struct s_rect{
	int	xpos;
	int	ypos;
	int	deg;
	int	rotx;
	int	roty;
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
