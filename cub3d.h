#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define HEIGHT 600
#define WIDTH 600

/*Key kode define*/
#define KEY_UP 126
#define KEY_DN 125
#define KEY_RG 124
#define KEY_LE 123
#define KEY_W 13
#define KEY_S 1
#define KEY_D 2
#define KEY_A 0
#define ESC 53

#ifdef __linux__
	#define KEY_UP 115
	#define KEY_DN 119
	#define KEY_RG 100
	#define KEY_LE 6536
	#define KEY_W 65361
	#define KEY_S 65307
	#define KEY_D
	#define KEY_A
#endif
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
